#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <Network.hpp>
#include <Plot.hpp>
#include <Physics.hpp>

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */
class Simulation
{
    public:
		/// in case of analytic no argument needed -> time stepping is not in option, it will be 1 by default
        Simulation(Physics:Time const& time_of_simulation); 
        Simulation(Physics:Time const& time_of_simulation, Type const& type,
					Physics:Time const& time_step,
					Physics::Resistance const& resistance);
        virtual ~Simulation();
        void launch_simulation();

    private:
        Network network_;
        Plot plot_;
        Physics::Time time_of_simulation_;
        Physics::Time time_step_;
};

#endif // SIMULATION_HPP
