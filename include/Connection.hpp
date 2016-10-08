#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>

#include <physics.hpp>
#include <Neuron.hpp>

/**
 * @brief Connection between two neurons or with the surrounding
 *
 * Provide a link to show where the electrical current need to go.
 */
class Connection
{
public:
    Connection(/* arguments */);
    virtual ~Connection();

private:
    std::unique_ptr<Neuron> target_neuron_;
    physics::Potential postsynaptic_potential_amplitude_;
};

#endif // CONNECTION_HPP
