#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"


TEST(AnalyticNeuronTests, TestStep)
{
    Neuron neurone(SimulationType::Analytic, true);
    int dt = 1;
    neurone.Neuron::step(1);
    int result = neurone.get_Vm();
    
    std::cout << result << std::endl;

    EXPECT_NEAR (6.658, neurone.get_Vm(),  0.000001);
    EXPECT_TRUE(abs(neurone.get_Vm() - 6.658) < 0.000001);
}


TEST(AnalyticNeuronTests, TestSingleNeuronSimulation)
{
    Physics::Time time = 1000; //ms
    Simulation sim(time, 1);
    sim.launch_simulation();
    EXPECT_TRUE(true);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


