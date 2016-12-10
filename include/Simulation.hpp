#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <gtest/gtest.h>

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
                    bool const& add_external_current = true,
                    std::vector<unsigned int>* neuron_csv_files = NULL,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = EXTERNAL_FACTOR,
                    unsigned random_seed = RANDOM_SEED );


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
                    bool const& add_external_current = true,
                    std::vector<unsigned int>* neuron_csv_files = NULL,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = EXTERNAL_FACTOR,
                    unsigned random_seed = RANDOM_SEED);

        virtual ~Simulation();
        void launch_simulation();
        Physics::Time get_simulation_time();

    private:
        Network * get_network();

    private:
        Network network_;
        Physics::Time time_of_simulation_;
        Physics::Time time_step_;

    private:
        FRIEND_TEST(AnalyticNeuronTests, TestSingleNeuronSimulation);
        FRIEND_TEST(AnalyticNeuronTests, TestDecayNeuronVoltage);
        FRIEND_TEST(ExplicitNeuronTests, TestSingleNeuronSimulation);
        FRIEND_TEST(ExplicitNeuronTests, TestDecayNeuronVoltage);
        FRIEND_TEST(ImplicitNeuronTests, TestSingleNeuronSimulation);
        FRIEND_TEST(ImplicitNeuronTests, TestDecayNeuronVoltage);
};

#endif // SIMULATION_HPP
