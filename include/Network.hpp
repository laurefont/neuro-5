#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include <Neuron.hpp>
#include <ExternalNeuron.hpp>
#include <Physics.hpp>

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
	///
	Network(Type const type, unsigned int const number_neurons, double const gamma, double const epsilon,
			Physics::Frequency const ext_f, Physics::Resistance const membrane_resistance);
	Network(Network const &) = delete;
	Network& operator=(Network const &) = delete;

	virtual ~Network();

	///
	/// Update each neurons of the network
	///
	/// @param dt time interval
	void update(Physics::Time dt);

private:
	///
	/// Create connections between neurons
	///
	/// Each neurons has epsilon_ chance to make a connection with each other neurons
	///
	void make_connections();

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
	/// external frequency
	///
	Physics::Frequency const ext_f_;

	///
	/// membrane resistance
	///
	Physics::Resistance membrane_resistance_;

	///
	/// Type of solution
	///
	Type const type_;

	std::vector<Neuron> neurons_;
	std::vector<ExternalNeuron> connections_from_surroundings_;
};

#endif // NETWORK_HPP
