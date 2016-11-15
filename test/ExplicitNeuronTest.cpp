#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ExplicitNeuronTests, TestThreshold)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3);
    neurone.set_Vm_ (25);
    neurone.Neuron::has_reached_threshold();
    int result = neurone.has_reached_threshold();

    EXPECT_EQ (true, result);
    EXPECT_TRUE(result==true);
}

TEST(ExplicitNeuronTests, TestStep)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3);
    neurone.set_Vm_ (7); 
    neurone.set_I_(5); 
    int dt = 1; 
    neurone.Neuron::step(1);
    int result = neurone.get_Vm_();
    
    EXPECT_NEAR (7.4, neurone.get_Vm_(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm_() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestStepExplicit)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3);
    neurone.set_Vm_ (7); 
    neurone.set_I_(5); 
    int dt = 1; 
    
    neurone.Neuron::step_explicit(1);
    
    int result = neurone.get_Vm_();
       
    EXPECT_NEAR (7.4, neurone.get_Vm_(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm_() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestResetPotential)
{
    Neuron neurone(Type::Explicit, true, 1, 1, 3);
    neurone.set_Vm_ (25);
    neurone.Neuron::reset_potential();
    
    int result = neurone.get_Vm_();

    EXPECT_EQ (10, result);
    EXPECT_TRUE(result==10);
}

/*TEST(ExplicitNeuronTests, TestSetConnections)
{
    Neuron neurone1(Type::Explicit, true, 1, 1, 3);
    Neuron neurone2(Type::Explicit, true, 1, 1, 3);
    neurone1.set_Vm_ (25);
    neurone1.set_I_ (10);
    neurone2.set_Vm_(25);
    neurone2.set_I_(10);
    int dt(1);
    neurone1.Neuron::set_connection(&neurone2);
    
    int result = neurone1.synapses_.size();

    EXPECT_EQ (1251, result); //initial size is 1250
    EXPECT_TRUE(result==1251);
}
*/
  
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


