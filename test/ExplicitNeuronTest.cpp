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

    EXPECT_EQ (1, result); 
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

TEST(ExplicitNeuronTests, TestInput)
{
    Neuron neuron1(Type::Explicit, true, 1, 1, 1, 25, 20, 0, 3);
    
    int dt(3);
    
    Event event1(1, 1.0);

    neuron1.Neuron::add_event_in(event1); 
      
    neuron1.Neuron::input(dt); 
                             
    double result1 = neuron1.get_I();
    double result2 = neuron1.get_Vm();
    
    
    EXPECT_NEAR (20.1, result1,  0.000001);   
    EXPECT_TRUE(abs(result1 - 20.1) < 0.000001);
   
    EXPECT_NEAR (24.25, result2,  0.02);   
    EXPECT_TRUE(abs(result2 - 24.25) < 0.02);
    
   
}

TEST(ExplicitNeuronTests, TestUpdate)
{
    Neuron neuron1(Type::Explicit, true, 1, 1, 1, 25, 20, 0, 3);
    Neuron neuron2(Type::Explicit, true, 1, 1, 1, 25, 20, 0, 3);
    
    int dt(3);
    
    double i(10.0);
    
    Event event1(1, 1.0);

    neuron1.Neuron::add_event_in(event1); 
    neuron1.Neuron::set_connection(&neuron2);
    
    neuron1.Neuron::update(dt);
                             
    double result1 = neuron1.get_I();
    double result2 = neuron1.get_Vm();
    int result3 = neuron1.get_event_in_size(); 
    int result4 = neuron1.get_synapses_size();
    int result5 = neuron2.get_event_in_size();
    double result6 = neuron2.get_I();
    double result7 = neuron2.get_Vm();
   
    //neuron1.get_refractory_period(); 
    
    EXPECT_NEAR (0.0, result1,  0.000001);   
    EXPECT_TRUE(abs(result1 - 0.0) < 0.000001);
   
    EXPECT_NEAR (10.0, result2,  0.000001);   
    EXPECT_TRUE(abs(result2 - 10.0) < 0.000001);
    
   
    EXPECT_EQ (0, result3); 
    EXPECT_TRUE(result3==0);
    
    EXPECT_EQ (1, result4); 
    EXPECT_TRUE(result4==1);
   
    EXPECT_EQ (1, result5); 
    EXPECT_TRUE(result5==1);
    
    
    EXPECT_NEAR (20.0, result6,  0.000001);   
    EXPECT_TRUE(abs(result6 - 20.0) < 0.000001);
   
    EXPECT_NEAR (25.0, result7,  0.000001);   
    EXPECT_TRUE(abs(result7 - 25.0) < 0.000001);
    
   
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


