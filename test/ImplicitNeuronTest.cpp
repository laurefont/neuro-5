#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

#define TestsCategoryName ImplicitNeuronTests
#define NeuronType SimulationType::ImplicitBackwardEuler

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

    EXPECT_EQ ((1+initial_size), result); //initial size is 0
    EXPECT_TRUE(result==(1+initial_size));
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

    neuron1.Neuron::add_connection(&neuron2);   //ajout de neuron2 au tableau de synapses de neuron1
    neuron1.output(i);                          //ajoute un event à neuron2
    int result = neuron2.get_event_in_size();

    EXPECT_EQ ((1+initial_size), result); //initial size is 0
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
    Physics::Time dt = 1;
    Event event1(0.9, 1.0);
    neuron1.add_event_in(event1); //make neuron1 spike

    Physics::Potential vm1_rest = neuron1.get_Vm();
    neuron1.set_Vm(FIRING_THRESHOLD);
    Physics::Potential vm1_fire_thr = neuron1.get_Vm();
    neuron1.update(dt);
    Physics::Potential vm1_reset = neuron1.get_Vm();
    size_t synapses_size1 = neuron1.get_synapses_size();
    size_t events_size2 = neuron2.get_event_in_size();

    //step neuron 2 until receival of spike of neuron 1
    for (Physics::Time t=0; t< 0.9+TRANSMISSION_DELAY; t+=dt)
        neuron2.update(dt); //step neuron 2

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
    EXPECT_NEAR (WEIGHT_J_EXC*0.1, vm2,  0.1);
}

TEST(TestsCategoryName, TestDecayNeuronVoltage)
{
    Simulation simulation( 1, 200, 0.1, SimulationType::ImplicitBackwardEuler, false, NULL);
    simulation.get_network()->get_neuron(0)->set_Vm(10);
    simulation.launch_simulation();
    Physics::Potential vm = simulation.get_network()->get_neuron(0)->get_Vm();
    EXPECT_NEAR(vm, RESTING_POTENTIAL, 0.001);
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
					EXTERNAL_FACTOR, RANDOM_SEED, true, 2);
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
