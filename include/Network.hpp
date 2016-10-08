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

private:
    std::vector<Neuron> neurons_;
    std::vector<Connection> connections_from_surroundings_;
};

#endif // NETWORK_HPP
