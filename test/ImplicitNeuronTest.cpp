#include <cmath>
#include <gtest/gtest.h>
#include "Simulation.hpp"

TEST(ImplicitNeuronTests, TestThreshold)
{
    Neuron neuron(Type::Implicit, true, 0.5);
    neuron.Neuron::has_reached_threshold();
    int result = neuron.has_reached_threshold();

    EXPECT_EQ (true, result);
    EXPECT_TRUE(result==true);
}

TEST(ImplicitNeuronTests, TestStep)
{
    Neuron neuron1(Type::Implicit, true, 0.5);
    Neuron neuron2(Type::Implicit, true, 0.5);
    Neuron neuron3(Type::Implicit, true, 0.5);
    
    int dt_1 = 1; 
    neuron1.Neuron::step(dt_1);
    
    int dt_2 = 2;
    neuron2.Neuron::step(dt_2);
    
    int dt_3 = 10;
    neuron3.Neuron::step(dt_3);
    
    EXPECT_NEAR (7.381, neuron1.get_Vm(),  0.001);
    EXPECT_TRUE(abs(neuron1.get_Vm() - 7.381) < 0.001);
    
    EXPECT_NEAR (13.641, neuron2.get_Vm(),  0.001);
    EXPECT_TRUE(abs(neuron2.get_Vm() - 13.64) < 0.001);
    
    EXPECT_NEAR (39.333, neuron3.get_Vm(),  0.001);
    EXPECT_TRUE(abs(neuron3.get_Vm() - 39.333) < 0.001);
    
    
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


