#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <Neuron.hpp>
#include <Network.hpp>
#include <Physics.hpp>

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */
class Simulation
{
    public:
		/// 
		/// Create a simulation 
		///
		/// @param time_of_simulation duration of the simulation
		/// @param time_step time step duration
		/// @param type type of solution
		/// @param number_neurons number of neurons in the network
		/// @param gamma proportion of inhibitory neurons over excitatory neurons
		/// @param epsilon connections density
		/// @param membrane_resistance membrane resistance
		/// @param ext_f external frequency
		///
        Simulation(Physics::Time const& time_of_simulation, Physics::Time const& time_step, Type const& type,
					unsigned int const number_neurons, double const gamma, double const epsilon,
					Physics::Resistance const& membrane_resistance, Physics::Frequency ext_f);

		/// 
		/// Create a simulation with an analytic solution
		///
		/// time stepping is not in option, it will be 1 by default
		///
		/// @param time_of_simulation duration of the simulation
		/// @param number_neurons number of neurons in the network
		/// @param gamma proportion of inhibitory neurons over excitatory neurons
		/// @param epsilon connections density
		/// @param membrane_resistance membrane resistance
		/// @param ext_f external frequency
		///
        Simulation(Physics::Time const& time_of_simulation,
                    unsigned int const number_neurons, double const gamma, double const epsilon,
                    Physics::Resistance const& membrane_resistance, Physics::Frequency ext_f);

        ~Simulation();
        void launch_simulation();

    private:
        Network network_;

        Physics::Time time_of_simulation_;
		Physics::Time time_step_;
};

#endif // SIMULATION_HPP
