#include "Neuron.hpp"


Neuron::Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f) : excitatory_(exc), inhib_connections_(250), excit_connections_(1000), epsilon_(eps), tau_(20), ext_f_(ext_f), firing_threshold_(20), rest_potential_(10),transmission_delay_(1.5), refactory_period_(2), amplitude_(0.1)
{
}

