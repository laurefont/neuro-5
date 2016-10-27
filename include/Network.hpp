#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <Neuron.hpp>

///
/// @brief Sparsely connected network of neurons
///
class Network
{
public:
	/// 
	/// Create a network of excitatory and inhibitatory neurons.
	///
	/// The copy constructor and assignment operator are deleted.
	/// 
	Network(int number_excitatory_neurons, int number_inhibitory_neurons);
	Network(const Network&) = delete;
	Network& operator=(const Network&) = delete;

	virtual ~Network();

	void update(/* arguments */);

private:
	int N_; /// total number of neurons
	int Ne_; /// number of excitatory neurons
	int Ni_; /// number of inhibitatory neurons
	std::vector<Neuron> neurons_;
	std::vector<ExternalNeuron> connections_from_surroundings_;
};

#endif // NETWORK_HPP
