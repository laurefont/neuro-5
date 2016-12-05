#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>
#include <fstream>      // std::ofstream

#include <Physics.hpp>
#include <Neuron.hpp>
#include <ExternalNeuron.hpp>

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
	/// Create a network of excitatory and inhibitory neurons.
	///
	/// @param type type of solution
	/// @param number_neurons number of neurons in the network
	/// @param gamma proportion of inhibitory neurons over excitatory neurons
	/// @param epsilon connections density
	/// @param membrane_resistance membrane resistance
	/// @param ext_f external frequency
    /// @param refractory_period refractory period
    ///
    Network(SimulationType const& type,
            unsigned int const& number_neurons,
            bool const& add_external_current = true,
            std::vector<unsigned int>* output_neuron_ids = NULL,
            double const& gamma = GAMMA,
            double const& epsilon = EPSILON,
            double const& external_factor = EXTERNAL_FACTOR,
            Physics::Potential firing_threshold = FIRING_THRESHOLD,
            Physics::Time refractory_period = REFRACTORY_PERIOD,
            Physics::Potential resting_potential = RESTING_POTENTIAL,
            Physics::Potential reset_potential = RESET_POTENTIAL,
            Physics::Time transmission_delay = TRANSMISSION_DELAY,
            Physics::Time tau = TAU,
            Physics::Time time_of_simulation = SIMULATION_TIME, 
            double initial_Vm = RESTING_POTENTIAL );
            
	Network(Network const &) = delete;
	Network& operator=(Network const &) = delete;

	virtual ~Network();

	///
	/// Update each neurons of the network
	///
	/// @param dt time interval
    Physics::Time update(Physics::Time dt);

    Neuron* get_neuron(unsigned int n);

    size_t get_neurons_size();

private:
	///
	/// Create connections between neurons
	///
	/// Each neurons has epsilon_ chance to make a connection with each other neurons
	///
	void make_connections();
	
	///
	/// Returns time of the almost last neuron and index of the last neuron
	///
    Neuron_last get_last_neurons();

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

    SimulationType const type_; ///< type of simulation (analytical, explicit, implicit)
	
	
};

#endif // NETWORK_HPP
