#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ImplicitNeuronTests, TestFiring)
{
    Neuron neurone(Type::Implicit, true, 1, 1, 3, 7, 5);
    int dt = 1;
    neurone.Neuron::step_implicit(1);
    int result = neurone.get_Vm();

    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(ExplicitNeuronTests, TestStep)
{
    Neuron neuron(Type::Implicit, true, 1, 1, 3, 7, 5); 
    int dt = 1; 
    neuron.Neuron::step(1);
    int result = neuron.get_Vm();
    
    EXPECT_NEAR (7.4, neuron.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neuron.get_Vm() - 7.4) < 0.000001);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


