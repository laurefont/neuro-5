#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(AnalyticNeuronTests, TestFiring)
{
    Neuron neurone(Type::Analytic, true, 1, 1, 3, 7, 5);
    int dt = 1;
    neurone.Neuron::step_analytic(1);
    int result = neurone.get_Vm();

    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

TEST(AnalyticNeuronTests, TestAnalytic)
{
    Neuron neurone(Type::Analytic, true, 1, 1, 3, 7, 5);
    int dt = 1;

    neurone.Neuron::step_analytic(1);

    int result = neurone.get_Vm();

    EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


