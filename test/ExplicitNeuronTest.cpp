#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ExplicitNeuronTests, TestThreshold)
{
    Neuron neurone(SimulationType::Explicit, true);
    neurone.Neuron::has_reached_threshold();
    int result = neurone.has_reached_threshold();

    EXPECT_EQ (true, result);
    EXPECT_TRUE(result==true);
}

TEST(ExplicitNeuronTests, TestStep)
{
    Neuron neurone(SimulationType::Explicit, true);
    int dt = 1; 
    neurone.Neuron::step(1);
    int result = neurone.get_Vm();
    
    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestStepExplicit)
{
    Neuron neurone(SimulationType::Explicit, true, 0.5);
    int dt = 1; 
    
    neurone.Neuron::step(1);
    
    int result = neurone.get_Vm();
       
    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestResetPotential)
{
    Neuron neurone(SimulationType::Explicit, true);
    neurone.Neuron::reset_potential();
    
    int result = neurone.get_Vm();

    EXPECT_EQ (10, result);
    EXPECT_TRUE(result==10);
}

TEST(ExplicitNeuronTests, TestSetConnections)
{
    Neuron neurone1(SimulationType::Explicit, true);
    Neuron neurone2(SimulationType::Explicit, true);
    int dt(1);
    neurone1.Neuron::add_connection(&neurone2);
    
    int result = neurone1.get_synapses_size();

    EXPECT_EQ (1, result); 
    EXPECT_TRUE(result==1);
}

TEST(ExplicitNeuronTests, TestAddEvent)
{
    Neuron neuron1(SimulationType::Explicit, true);
   
    Event event1(1, 1.0);
    
    neuron1.add_event_in(event1);
    int result = neuron1.get_event_in_size();
    
    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
}



TEST(ExplicitNeuronTests, TestUpdate_RI)
{
    Neuron neuron1(SimulationType::Explicit, true);
   
    Event event1(1, 1.0);
    
    neuron1.add_event_in(event1);
    
    int dt(3);
    Physics::Amplitude RI = neuron1.RI(dt);
    
    EXPECT_NEAR (10.1, RI,  0.000001);   //initial current = 10 and membrane_resistance = 1
    EXPECT_TRUE(abs(RI - 10.1) < 0.000001);
}

TEST(ExplicitNeuronTests, TestOutput)
{
    Neuron neuron1(SimulationType::Explicit, true);
    Neuron neuron2(SimulationType::Explicit, true);
    double i(10.0);

    neuron1.Neuron::add_connection(&neuron2);   //ajout de neuron2 au tableau de synapses de neuron1
    neuron1.output(i);                          //ajoute un event à neuron2
    int result = neuron2.get_event_in_size();
    
    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
    
}

TEST(ExplicitNeuronTests, TestInput)
{
    Neuron neuron1(SimulationType::Explicit, true);
    
    int dt(3);
    
    Event event1(1, 1.0);

    neuron1.Neuron::add_event_in(event1); 
    Physics::Amplitude RI = neuron1.RI(dt);
    EXPECT_NEAR (20.1, RI,  0.000001);
    EXPECT_TRUE(abs(RI - 20.1) < 0.000001);
   
    Physics::Potential vm = neuron1.get_Vm();
    EXPECT_NEAR (24.25, vm,  0.02);
    EXPECT_TRUE(abs(vm - 24.25) < 0.02);
}

TEST(ExplicitNeuronTests, TestUpdate)
{
    Neuron neuron1(SimulationType::Explicit, true);
    Neuron neuron2(SimulationType::Explicit, true);
    
    int dt(3);
    
    double i(10.0);
    
    Event event1(1, 1.0);

    neuron1.Neuron::add_event_in(event1); 
    neuron1.Neuron::add_connection(&neuron2);
    neuron1.Neuron::update(dt);
                             
    double vm1 = neuron1.get_Vm();
    int result3 = neuron1.get_event_in_size(); 
    int result4 = neuron1.get_synapses_size();
    int result5 = neuron2.get_event_in_size();
    double vm2 = neuron2.get_Vm();
   
    EXPECT_NEAR (10.0, vm1,  0.000001);
    EXPECT_TRUE(abs(vm1 - 10.0) < 0.000001);
    
    EXPECT_EQ (0, result3); 
    EXPECT_TRUE(result3==0);
    
    EXPECT_EQ (1, result4); 
    EXPECT_TRUE(result4==1);
   
    EXPECT_EQ (1, result5); 
    EXPECT_TRUE(result5==1);
    
    EXPECT_NEAR (25.0, vm2,  0.000001);
    EXPECT_TRUE(abs(vm2 - 25.0) < 0.000001);
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


