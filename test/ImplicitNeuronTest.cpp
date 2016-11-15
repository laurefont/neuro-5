#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ImplicitNeuronTests, TestFiring)
{
    Neuron neurone(Type::Implicit, true, 1, 1, 3);
    neurone.set_Vm_ (7);
    neurone.set_I_(5);
    int dt = 1;
    neurone.Neuron::step_implicit(1);
    int result = neurone.get_Vm_();

    EXPECT_NEAR (7.4, neurone.get_Vm_(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm_() - 7.4) < 0.000001);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


