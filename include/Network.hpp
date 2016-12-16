#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>
#include <fstream>

#include <gtest/gtest.h>

#include <Physics.hpp>
#include <Neuron.hpp>

///
/// @brief structure used to return the latest neuron in time and the time of almost last neuron in time in method get_back_neuron
///
struct Neuron_last 
{
    int last_id;
    int second_last_id;
};
    
///
/// @brief Sparsely connected network of neurons
///
/// This model assume that the connection density is small: the number of 
/// excitatory connections over the number of excitatory neurons is equal
/// to the number of inhibitory connections over the number of inhibitory
/// neurons and is much less than 1.
///
/// \f$\epsilon = C_e/N_e = C_i/N_i \ll 1\f$
///
class Network
{
public:
    /// 
    /// @brief Constructor
    ///
    /// Create a network of excitatory and inhibitory neurons.
    ///
    /// @param type type of solution
    /// @param number_neurons number of neurons in the network
    /// @param add_external_current presence of external current arriving
    /// @param output_neuron_ids neurons that will output a file
    /// @param gamma proportion of inhibitory neurons over excitatory neurons
    /// @param epsilon connections density
    /// @param external_factor external factor
    /// @param random_seed seed for the random generators
    /// @param firing_threshold firing threshold
    /// @param refractory_period refractory period duration
    /// @param resting_potential resting potential at equilibrium state
    /// @param reset_potential reset potential after a neuron has fired
    /// @param transmission_delay duration of a spike transmission
    /// @param tau neuron membrane time constant
    /// @param time_of_simulation duration of the simulation
    /// @param spike_interval spike counting time interval for output files
    ///
    Network(SimulationType const& type,
            unsigned int const& number_neurons,
            bool const& add_external_current = true,
            std::vector<unsigned int>* output_neuron_ids = NULL,
            double const& gamma = GAMMA,
            double const& epsilon = EPSILON,
            double const& external_factor = EXTERNAL_FACTOR,
            unsigned random_seed = RANDOM_SEED,
            Physics::Potential firing_threshold = FIRING_THRESHOLD,
            Physics::Time refractory_period = REFRACTORY_PERIOD,
            Physics::Potential resting_potential = RESTING_POTENTIAL,
            Physics::Potential reset_potential = RESET_POTENTIAL,
            Physics::Time transmission_delay = TRANSMISSION_DELAY,
            Physics::Time tau = TAU,
            Physics::Time time_of_simulation = SIMULATION_TIME,
            Physics::Time spike_interval = SPIKE_INTERVAL );
            
    Network(Network const &) = delete;
    Network& operator=(Network const &) = delete;

    ///
    /// @brief Destructor
    ///
    ~Network();

    ///
    /// Update each neurons of the network
    ///
    /// @param dt time interval
    ///
    Physics::Time update(Physics::Time dt);

    ///
    /// @brief write to an output file the number of spike for each time interval
    ///
    void write_spikes_to_file();

private:
    ///
    /// Create connections between neurons
    ///
    /// Each neurons has epsilon_ chance to make a connection with each other neurons
    ///
    void make_connections(unsigned seed);
    
    ///
    /// Returns time of the almost last neuron and index of the last neuron
    ///
    Neuron_last get_last_neurons();

    ///
    /// @brief Get a neuron of the network
    ///
    /// Used for test
    ///
    /// @param n neuron id
    /// @return pointer to the neuron
    ///
    Neuron* get_neuron(unsigned int n);

private:
    unsigned int const N_; ///< total number of neurons
    unsigned int const Ne_; ///< number of excitatory neurons
    unsigned int const Ni_; ///< number of inhibitory neurons

    /// 
    /// @brief Proportion of connections and neurons
    ///
    /// \f$\gamma = C_i/C_e = N_i/N_e\f$
    ///
    double const gamma_; 

    ///
    /// @brief Connection density
    ///
    /// \f$\epsilon = C_e/N_e = C_i/N_i \ll 1\f$
    ///
    double const epsilon_;

    ///
    /// @brief Neurons of the network
    ///
    Neuron** neurons_;
    
    std::ofstream * raster_plot_file; ///< output file for raster plot
    std::ofstream * spike_file; ///< output file of firing rate

    SimulationType const type_; ///< type of simulation (analytical, explicit, implicit)

    unsigned int* spike_times_;

    Physics::Time time_of_simulation_;
    
    Physics::Time spike_interval_;
    
private:
    FRIEND_TEST(AnalyticNeuronTests, TestSingleNeuronSimulation);
    FRIEND_TEST(AnalyticNeuronTests, TestDecayNeuronVoltage);

    FRIEND_TEST(ExplicitNeuronTests, TestDecayNeuronVoltage);

    FRIEND_TEST(ImplicitNeuronTests, TestDecayNeuronVoltage);
};

#endif // NETWORK_HPP
