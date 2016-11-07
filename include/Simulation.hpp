#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <Network.hpp>
#include <Plot.hpp>

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */
class Simulation
{
    public:
        Simulation(/* arguments */);
        virtual ~Simulation();

    private:
        Network network_;
        Plot plot_;
};

#endif // SIMULATION_HPP
