#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <Neuron.hpp>
#include <Network.hpp>
#include <Physics.hpp>

//see page 9 here for parameters:
//http://arken.nmbu.no//~plesser/publications/Gewa_2012_533_preprint.pdf
#define FIRING_THRESHOLD 20
#define RESTING_POTENTIAL 0
#define RESET_POTENTIAL 10
#define REFRACTORY_PERIOD 2
#define TRANSMISSION_DELAY 1.5
#define TAU 20 //from Brunel 2000 paper
#define WEIGHT_EXC 1
#define WEIGHT_INH -0.5
#define MEMBRANE_RESISTANCE 1/5.0

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
		/// @param external_factor external factor
        /// @param refractory_period_ refractory period
        ///
        Simulation(Physics::Time const& time_of_simulation, Physics::Time const& time_step, Type const& type,
					unsigned int const number_neurons, double const gamma, double const epsilon,
                    Physics::Resistance const& membrane_resistance, double const& external_factor,
                    Physics::Time refractory_period_);

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
		/// @param external_factor external factor
		///
        Simulation(Physics::Time const& time_of_simulation, unsigned int const number_neurons,
					double const gamma, double const epsilon, Physics::Resistance const& membrane_resistance, 
                    double const& external_factor, Physics::Time refractory_period_);

        virtual ~Simulation();
        void launch_simulation();

    private:
        Network network_;

        Physics::Time time_of_simulation_;
		Physics::Time time_step_;
};

#endif // SIMULATION_HPP
