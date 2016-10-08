#ifndef NEURONS_HPP
#define NEURONS_HPP

#include <physics.hpp>
#include <Connection.hpp>

/**
 * @brief Represent a single neuron
 *
 * This class represent a single excitatory or inhibitory neuron.
 * It use the Leaky Integrate and Fire model.
 */
class Neurons
{
public:
    Neurons(/* arguments */);
    virtual ~Neurons();

private:
    bool excitatory_;
    Connection neuron_targeted_by_axon_;
    physics::Potential potential_;
    static const physics::Potential firing_threshold_;
    static const physics::Potential rest_potential_;
    static const physics::Time transmission_delay_;
    static const physics::Time refactory_period_;
};

#endif // NEURONS_HPP
