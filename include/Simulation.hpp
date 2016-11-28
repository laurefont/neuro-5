#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <Physics.hpp>
#include <Network.hpp>

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */
class Simulation
{
    public:
        ///
        /// Create a fix step method simulation
        ///
        /// @param number_neurons number of neurons in the network
        /// @param time_of_simulation duration of the simulation
        /// @param time_step time step duration
        /// @param type type of solution
        /// @param gamma proportion of inhibitory neurons over excitatory neurons
        /// @param epsilon connections density
        /// @param external_factor external factor
        ///
        Simulation( unsigned int const number_neurons,
                    Physics::Time const& time_of_simulation,
                    Physics::Time const& time_step,
                    SimulationType const& type,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = 0);

        ///
        /// Create a simulation with an analytic solution
        ///
        /// @param number_neurons number of neurons in the network
        /// @param time_of_simulation duration of the simulation
        /// @param gamma proportion of inhibitory neurons over excitatory neurons
        /// @param epsilon connections density
        /// @param external_factor external factor
        ///
        Simulation( unsigned int const number_neurons,
                    Physics::Time const& time_of_simulation,
                    std::vector<unsigned> * output_neuron_ids = NULL,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,\
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = 0.5);

        virtual ~Simulation();
        void launch_simulation();
        Network * get_network();
        Physics::Time get_simulation_time();

    private:
        Network network_;
        Physics::Time time_of_simulation_;
        Physics::Time time_step_;
};

#endif // SIMULATION_HPP
