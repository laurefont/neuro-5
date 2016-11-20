#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ExplicitNeuronTests, TestThreshold)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3, 25);
    neurone.Neuron::has_reached_threshold();
    int result = neurone.has_reached_threshold();

    EXPECT_EQ (true, result);
    EXPECT_TRUE(result==true);
}

TEST(ExplicitNeuronTests, TestStep)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3, 7, 5);
    int dt = 1; 
    neurone.Neuron::step(1);
    int result = neurone.get_Vm();
    
    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestStepExplicit)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3, 7, 5);
    int dt = 1; 
    
    neurone.Neuron::step_explicit(1);
    
    int result = neurone.get_Vm();
       
    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestResetPotential)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3, 25);
    neurone.Neuron::reset_potential();
    
    int result = neurone.get_Vm();

    EXPECT_EQ (10, result);
    EXPECT_TRUE(result==10);
}

TEST(ExplicitNeuronTests, TestSetConnections)
{
    Neuron neurone1(Type::Explicit, true, 1, 1, 3, 25, 10);
    Neuron neurone2(Type::Explicit, true, 1, 1, 3, 25, 10);
    int dt(1);
    neurone1.Neuron::set_connection(&neurone2);
    
    int result = neurone1.get_synapses_size();

    EXPECT_EQ (1, result); //initial size is 1250
    EXPECT_TRUE(result==1);
}

TEST(ExplicitNeuronTests, TestAddEvent)
{
    Neuron neuron1(Type::Explicit, true, 1, 1, 1, 25, 10, 3);
   
    Event event1(1, 1.0);
    
    neuron1.add_event_in(event1);
    int result = neuron1.get_event_in_size();
    
    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
}



TEST(ExplicitNeuronTests, TestUpdate_RI)
{
    Neuron neuron1(Type::Explicit, true, 1, 1, 1, 25, 10, 0, 3);
   
    Event event1(1, 1.0);
    
    neuron1.add_event_in(event1);
    
    int dt(3);
    neuron1.update_RI(dt);
    
    
    double result = neuron1.get_I();
    
    EXPECT_NEAR (10.1, neuron1.get_I(),  0.000001);   //initial current = 10 and membrane_resistance = 1
    EXPECT_TRUE(abs(neuron1.get_I() - 10.1) < 0.000001);
}

TEST(ExplicitNeuronTests, TestOutput)
{
    Neuron neuron1(Type::Explicit, true, 1, 1, 1, 25, 10, 0, 3);
    Neuron neuron2(Type::Explicit, true, 1, 1, 1, 25, 10, 0, 3);
   
    double i(10.0);

    neuron1.Neuron::set_connection(&neuron2);   //ajout de neuron2 au tableau de synapses de neuron1
    neuron1.output(i);                          //ajoute un event à neuron2
    int result = neuron2.get_event_in_size();
    
    EXPECT_EQ (1, result); //initial size is 0
    EXPECT_TRUE(result==1);
    
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


