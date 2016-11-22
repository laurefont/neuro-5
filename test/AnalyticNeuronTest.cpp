#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"


TEST(AnalyticNeuronTests, TestStep)
{
    Neuron neurone(Type::Analytic, true);
    int dt = 1;
    neurone.Neuron::step_analytic(1);
    int result = neurone.get_Vm();
    
    std::cout << result << std::endl;

    EXPECT_NEAR (6.658, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 6.658) < 0.000001);
}


TEST(AnalyticNeuronTests, TestSingleNeuronSimulation)
{
    Physics::Time time = 1000; //ms
    double gamma = 0.25; //from the paper
    double epsilon = 0.1;
    double membrane_resistance = 1/5; //from paper g=5
    double ext_f = 0;
    Physics::Time refractory_period_ = 2; //ms

    Simulation sim(time, 1, gamma, epsilon, membrane_resistance, ext_f, refractory_period_);
    sim.launch_simulation();
    EXPECT_TRUE(true);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


