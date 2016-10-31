#ifndef EXTERNAL_NEURON
#define EXTERNAL_NEURON

#include <memory>

#include <Physics.hpp>
#include <Neuron.hpp>

/**
 * @brief Connexions comming from outside the network
 *
 * Provide a link to show where the electrical current need to go.
 */
class ExternalNeuron
{
public:
    ExternalNeuron(/* arguments */);
    virtual ~ExternalNeuron();

private:
    std::unique_ptr<Neuron> target_neuron_;
    Physics::Potential postsynaptic_potential_amplitude_;
};

#endif // EXTERNAL_NEURON
