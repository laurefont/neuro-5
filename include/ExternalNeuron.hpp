#ifndef EXTERNAL_NEURON
#define EXTERNAL_NEURON

#include <memory>

#include <physics.hpp>
#include <Neuron.hpp>

/**
 * @brief Connexions comming from outside the network
 *
 * Provide a link to show where the electrical current need to go.
 */
class ExternalConnexion
{
public:
    ExternalConnexion(/* arguments */);
    virtual ~ExternalConnexion();

private:
    std::unique_ptr<Neuron> target_neuron_;
    physics::Potential postsynaptic_potential_amplitude_;
};

#endif // EXTERNAL_NEURON
