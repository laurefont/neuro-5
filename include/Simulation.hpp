#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <gtest/gtest.h>

#include <Physics.hpp>
#include <Network.hpp>

///
/// @brief The main class of the simulation
///
/// Make the simulation of the network.
///
class Simulation
{
public:
    ///
    /// Constructor
    ///
    /// Create a fixed-step method simulation
    ///
    /// @param number_neurons number of neurons in the network
    /// @param time_of_simulation duration of the simulation
    /// @param time_step time step duration
    /// @param type type of solution
    /// @param add_external_current presence of external current arriving
    /// @param neuron_csv_files neurons that will output a file
    /// @param firing_threshold firing threshold
    /// @param refractory_period refractory period duration
    /// @param resting_potential resting potential at equilibrium state
    /// @param reset_potential reset potential after a neuron has fired
    /// @param transmission_delay duration of a spike transmission
    /// @param tau neuron membrane time constant
    /// @param gamma proportion of inhibitory neurons over excitatory neurons
    /// @param epsilon connections density
    /// @param external_factor external factor
    /// @param random_seed seed for the random generators
    /// @param spike_interval spike counting time interval for output files
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
                unsigned random_seed = RANDOM_SEED,
                Physics::Time spike_interval = SPIKE_INTERVAL );

    ///
    /// Constructor
    ///
    /// Create a simulation with an analytic variable-step solution
    ///
    /// @param number_neurons number of neurons in the network
    /// @param time_of_simulation duration of the simulation
    /// @param add_external_current presence of external current arriving
    /// @param neuron_csv_files neurons that will output a file
    /// @param firing_threshold firing threshold
    /// @param refractory_period refractory period duration
    /// @param resting_potential resting potential at equilibrium state
    /// @param reset_potential reset potential after a neuron has fired
    /// @param transmission_delay duration of a spike transmission
    /// @param tau neuron membrane time constant
    /// @param gamma proportion of inhibitory neurons over excitatory neurons
    /// @param epsilon connections density
    /// @param external_factor external factor
    /// @param random_seed seed for the random generators
    /// @param spike_interval spike counting time interval for output files
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
                unsigned random_seed = RANDOM_SEED,
                Physics::Time spike_interval = SPIKE_INTERVAL );

    ///
    /// @brief Destructor
    ///
    ~Simulation();

    ///
    /// @brief launch the simulation
    ///
    void launch_simulation();

private:
    ///
    /// @brief Get the neurons network of the current simulation
    ///
    /// Used for test
    ///
    /// @return pointer to the network attribut
    ///
    Network * get_network();

    ///
    /// @brief Get the current simulation time
    ///
    /// Used for test
    ///
    /// @return the current simulation time
    ///
    Physics::Time get_simulation_time();

private:
    Network network_;
    Physics::Time time_of_simulation_;
    Physics::Time time_step_;
    Physics::Time spike_interval_;

private:
    FRIEND_TEST(AnalyticNeuronTests, TestSingleNeuronSimulation);
    FRIEND_TEST(AnalyticNeuronTests, TestDecayNeuronVoltage);

    FRIEND_TEST(ExplicitNeuronTests, TestDecayNeuronVoltage);

    FRIEND_TEST(ImplicitNeuronTests, TestDecayNeuronVoltage);
};

#endif // SIMULATION_HPP
