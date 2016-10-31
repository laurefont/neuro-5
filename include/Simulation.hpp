#pragma once

#include <Network.hpp>
#include <Plot.hpp>

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */

class Simulation: public Plot, public Neuron
{
public:
    Simulation(Neuron_State neuron_state, sf::Time);
    virtual ~Simulation();

private:
    Network network_;
    
    void update(); 
    
    double current_generator();
    
};
