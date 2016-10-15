#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <Neuron.hpp>

/**
 * @brief Sparsely connected network of neurons
 */
class Network
{
public:
	Network(/* arguments */);
	virtual ~Network();

	void update(/* arguments */);

private:
	int N_; /// total number of neurons
	int Ne_; /// number of excitatory neurons
	int Ni_; /// number of inhibitatory neurons
	std::vector<Neuron> neurons_;
	std::vector<Connection> connections_from_surroundings_;
};

#endif // NETWORK_HPP
