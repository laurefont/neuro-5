#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"


TEST(AnalyticNeuronTests, TestStep)
{
    Neuron neurone(Type::Analytic, true, 1, 1, 3, 7);
    int dt = 1;
    neurone.Neuron::step_analytic(1);
    int result = neurone.get_Vm();
    
    std::cout << result << std::endl;

    EXPECT_NEAR (6.658, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 6.658) < 0.000001);
    
    /*EXPECT_NEAR (7.4, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 7.4) < 0.000001);*/
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


