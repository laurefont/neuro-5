#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

#define TestsCategoryName AnalyticNeuronTests
#define NeuronType SimulationType::AnalyticVariableStep

TEST(TestsCategoryName, TestThreshold)
{
    Neuron neurone(NeuronType, true);
    Physics::Time dt = 1;
    Event event1(0.9, 1.0);
    neurone.add_event_in(event1); //make neuron spike
    neurone.set_Vm(FIRING_THRESHOLD);
    neurone.step(dt);

    EXPECT_TRUE( neurone.has_reached_threshold());
}

TEST(TestsCategoryName, TestResetPotential)
{
    Neuron neurone(NeuronType, true);
    neurone.Neuron::reset_potential();
    int result = neurone.get_Vm();

    EXPECT_EQ (RESET_POTENTIAL, result);
}

TEST(TestsCategoryName, TestSetConnections)
{
    Neuron neurone1(NeuronType, true);
    Neuron neurone2(NeuronType, true);
    neurone1.Neuron::add_connection(&neurone2);
    int result = neurone1.get_synapses_size();

    EXPECT_EQ (1, result);
    EXPECT_TRUE(result==1);
}

TEST(TestsCategoryName, TestAddEvent)
{
    Neuron neuron1(NeuronType, true);
    int initial_size = neuron1.get_event_in_size();
    Event event1(1, 1.0);
    neuron1.add_event_in(event1);
    int result = neuron1.get_event_in_size();

    EXPECT_EQ ((1+initial_size), result);
    EXPECT_TRUE(result==(initial_size +1));
}

TEST(TestsCategoryName, TestInputRI)
{
    Neuron neuron1(NeuronType, true, false); //no external current
    Event event1(1, 1);
    neuron1.add_event_in(event1);
    int dt(3);
    Physics::Amplitude RI = neuron1.RI(dt);

    EXPECT_NEAR ( TAU, RI,  0.000001);   //initial current = 10 and membrane_resistance = 1
}

TEST(TestsCategoryName, TestOutput)
{
    Neuron neuron1(NeuronType, true);
    Neuron neuron2(NeuronType, true);
    double i(10.0);

    int initial_size = neuron2.get_event_in_size();

    neuron1.Neuron::add_connection(&neuron2);   //create a connection (=1 synapse) between neuron1 and another neuron = neuron2
    neuron1.output(i);                          //add one event to neuron2
    int result = neuron2.get_event_in_size();

    EXPECT_EQ ((1+initial_size), result); //initial size isn't 0 anymore
    EXPECT_TRUE(result==(1+initial_size));
}

TEST(TestsCategoryName, TestSynapticConnetivity)
{
    Neuron neuron1(NeuronType, true, false); //no external current
    Neuron neuron2(NeuronType, true, false); //no external current

    int initial_synapse_size1 = neuron1.get_synapses_size();
    int initial_event_in_size2 = neuron2.get_event_in_size();

    neuron1.add_connection(&neuron2);

    //We set dt to transmission delay to be sure that:
    //- neuron1 processes event at time 0 and spikes at time dt
    //- neuron2 receives at time dt+TRANSMISSION DELAY and processes it
    //(accounting for the transmission delay)
    Physics::Time dt = 0.2;
    Event event1(0.1, WEIGHT_J_EXC*100);
    neuron1.add_event_in(event1); //make neuron1 spike

    Physics::Potential vm1_rest = neuron1.get_Vm();
    neuron1.set_Vm(FIRING_THRESHOLD);
    Physics::Potential vm1_fire_thr = neuron1.get_Vm();
    neuron1.update(dt);
    Physics::Potential vm1_reset = neuron1.get_Vm();
    size_t synapses_size1 = neuron1.get_synapses_size();
    size_t events_size2 = neuron2.get_event_in_size();

    //neuron1 transmits event at time 0.1+TRANSMISSION DELAY to neuron2
    neuron2.update(dt+TRANSMISSION_DELAY); //step neuron 2

    Physics::Potential vm2 = neuron2.get_Vm();

    //Test Neuron initialized at resting potential
    EXPECT_NEAR (RESTING_POTENTIAL, vm1_rest,  0.000001);

    //Test Neurons Firing Threshold
    EXPECT_NEAR (FIRING_THRESHOLD , vm1_fire_thr,  0.000001);

    //Test neuron VM set to reset potential after firing
    EXPECT_NEAR (RESET_POTENTIAL , vm1_reset,  0.000001);

    //Test insertion of synapses
    EXPECT_EQ ((1+initial_synapse_size1), synapses_size1);

    //Test event addition to neuron 2
    EXPECT_EQ ((1+initial_event_in_size2), events_size2);

    //test new voltage of neuron that received network current
    EXPECT_NEAR (WEIGHT_J_EXC, vm2,  0.1);
}

TEST(TestsCategoryName, TestSingleNeuronSimulation)
{
    Simulation sim( 1, // number_neurons,
                    100,
                    false,
                    NULL, //output_neuron_ids = NULL,
                    FIRING_THRESHOLD,
                    REFRACTORY_PERIOD,
                    RESTING_POTENTIAL,
                    RESET_POTENTIAL,
                    TRANSMISSION_DELAY,
                    TAU,
                    GAMMA,
                    EPSILON,
                    EXTERNAL_FACTOR ); //external_factor;

    Network * network = sim.get_network();
    Neuron * neuron1 = network->get_neuron(0);

    for (Physics::Time t=1; t<sim.get_simulation_time(); t++)
    {
        Physics::Amplitude J = WEIGHT_J_EXC;
        neuron1->add_event_in(Event(t,J));
    }

    sim.launch_simulation();
    EXPECT_TRUE(true); //if it runs successfully, return true
}

TEST(TestsCategoryName, TestDecayNeuronVoltage)
{
    Simulation simulation( 1, 100, false, NULL);
    simulation.get_network()->get_neuron(0)->set_Vm(10);
    simulation.launch_simulation();
    Physics::Potential vm = simulation.get_network()->get_neuron(0)->get_Vm();
    EXPECT_NEAR(vm, RESTING_POTENTIAL, 1.0);
}

TEST(TestsCategoryName, TestRefractoryPeriod)
{
	Neuron neuron (NeuronType, true, false, FIRING_THRESHOLD, SIMULATION_TIME, REFRACTORY_PERIOD, RESTING_POTENTIAL,RESET_POTENTIAL, TRANSMISSION_DELAY, TAU, 
					EXTERNAL_FACTOR, 25, true);
					
	Physics::Time dt = 0.1;
	for(Physics::Time i(0.0); i< 2.0 ; i+=dt)
	{
		neuron.update(dt);	
	}
	
	double result = neuron.get_Vm();
	EXPECT_EQ (RESTING_POTENTIAL, result);
	
}


TEST(TestsCategoryName, TestVolateFiringReset)
{
    Neuron neuron (NeuronType, true, false, FIRING_THRESHOLD, SIMULATION_TIME, REFRACTORY_PERIOD, RESTING_POTENTIAL,RESET_POTENTIAL, TRANSMISSION_DELAY, TAU, 
					EXTERNAL_FACTOR, RANDOM_SEED, true, 3);
    Physics::Time dt = TIME_STEP;
    Physics::Time DT = TIME_STEP;
    
    for(Physics::Time i(0.0); i< 20 ; i+=dt)
    {
		Event event(i,0.1);
		neuron.add_event_in(event); 
	}
	 for(Physics::Time i(20); i< 40 ; i+=dt)
    {
		Event event(i, 0.2);
		neuron.add_event_in(event); 
	}
	 for(Physics::Time i(40); i< 60 ; i+=dt)
    {
		Event event(i, 0.35);
		neuron.add_event_in(event); 
	}
	 for(Physics::Time i(60); i< 80 ; i+=dt)
    {
		Event event(i, 0.6);
		neuron.add_event_in(event); 
	}
	 for(Physics::Time i(80); i< 100 ; i+=dt)
    {
		Event event(i,1);
		neuron.add_event_in(event); 
	}
    while( neuron.get_t() < 100)
    {
		neuron.update(DT);
	}

}




int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
