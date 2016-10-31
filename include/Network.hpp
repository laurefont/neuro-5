#pragma once
#include <queue>
#include <Neuron.hpp>

///
/// @brief Sparsely connected network of neurons
///
class Network: Public Neuron
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

	void update(Neuron_State neuron_state, sf::Time);

private:
	int N_; /// total number of neurons
	int Ne_; /// number of excitatory neurons
	int Ni_; /// number of inhibitatory neurons
	std::priority_queue<Neuron> neurons_;
	std::queue<Connections> connections_from_surroundings_;
};

