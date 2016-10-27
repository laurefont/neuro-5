#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>

#include <Neuron.hpp>
#include <Physics.hpp>

///
/// @brief Sparsely connected network of neurons
///
class Network
{
public:
	/// 
	/// Create a network of excitatory and inhibitatory neurons.
	///
	/// @param number_neurons number of neurons in the network
	/// @param epsilon proportion of excitatory neurons over inhibitatory neurons
	Network(int number_neurons, double epsilon);
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
	void make_connections();

private:
	int N_; /// total number of neurons
	int Ne_; /// number of excitatory neurons
	int Ni_; /// number of inhibitatory neurons
	std::vector<Neuron> neurons_;
	std::vector<ExternalNeuron> connections_from_surroundings_;
};

#endif // NETWORK_HPP
