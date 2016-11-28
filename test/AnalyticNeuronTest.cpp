#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

#define TestsCategoryName AnalyticNeuronTests
#define NeuronType SimulationType::Analytic

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

TEST(TestsCategoryName, TestDecay)
{
    Neuron neurone(NeuronType, true);
    Physics::Time dt = 1;
    neurone.set_Vm(7);
    neurone.step(dt);
    Physics::Potential result = neurone.get_Vm();

    EXPECT_NEAR (6.6, result,  0.1);
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
    Event event1(1, 1.0);
    neuron1.add_event_in(event1);
    int result = neuron1.get_event_in_size();

    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
}

TEST(TestsCategoryName, TestInputRI)
{
    Neuron neuron1(NeuronType, true);
    Event event1(1, 1);
    neuron1.add_event_in(event1);
    int dt(3);
    Physics::Amplitude RI = neuron1.RI(dt);

    EXPECT_NEAR ( 20, RI,  0.000001);   //initial current = 10 and membrane_resistance = 1
    EXPECT_TRUE(abs(RI - 20) < 0.000001);
}

TEST(TestsCategoryName, TestOutput)
{
    Neuron neuron1(NeuronType, true);
    Neuron neuron2(NeuronType, true);
    double i(10.0);

    neuron1.Neuron::add_connection(&neuron2);   //ajout de neuron2 au tableau de synapses de neuron1
    neuron1.output(i);                          //ajoute un event à neuron2
    int result = neuron2.get_event_in_size();

    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
}

TEST(TestsCategoryName, TestSynapticConnetivity)
{
    Neuron neuron1(NeuronType, true);
    Neuron neuron2(NeuronType, true);
    neuron1.add_connection(&neuron2);

    //We set dt to transmission delay to be sure that:
    //- neuron1 processes event at time 0 and spikes at time dt
    //- neuron2 receives at time dt+TRANSMISSION DELAY and processes it
    //(accounting for the transmission delay)
    Physics::Time dt = 10;
    Event event1(0.9, 1.0);
    neuron1.add_event_in(event1); //make neuron1 spike

    Physics::Potential vm1_rest = neuron1.get_Vm();
    neuron1.set_Vm(FIRING_THRESHOLD);
    Physics::Potential vm1_fire_thr = neuron1.get_Vm();
    neuron1.update(dt);
    Physics::Potential vm1_reset = neuron1.get_Vm();
    size_t synapses_size1 = neuron1.get_synapses_size();
    size_t events_size2 = neuron2.get_event_in_size();

    neuron2.update(dt); //step neuron 2

    Physics::Potential vm2 = neuron2.get_Vm();

    //Test Neuron initialized at resting potential
    EXPECT_NEAR (RESTING_POTENTIAL, vm1_rest,  0.000001);

    //Test Neurons Firing Threshold
    EXPECT_NEAR (FIRING_THRESHOLD , vm1_fire_thr,  0.000001);

    //Test neuron VM set to reset potential after firing
    EXPECT_NEAR (RESET_POTENTIAL , vm1_reset,  0.000001);

    //Test insertion of synapses
    EXPECT_EQ (1, synapses_size1);

    //Test event addition to neuron 2
    EXPECT_EQ (1, events_size2);

    //test new voltage of neuron that received network current
    EXPECT_NEAR (2.4, vm2,  0.1);
}

TEST(TestsCategoryName, TestSingleNeuronSimulation)
{
    Simulation sim( 1, // number_neurons,
                    100,
                    NULL, //output_neuron_ids = NULL,
                    FIRING_THRESHOLD,
                    REFRACTORY_PERIOD,
                    RESTING_POTENTIAL,
                    RESET_POTENTIAL,
                    TRANSMISSION_DELAY,
                    TAU,
                    GAMMA,
                    EPSILON,
                    0.5 ); //external_factor;

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


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
