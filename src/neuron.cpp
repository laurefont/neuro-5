#include "neuron.hpp"


Neuron::Neuron() : teta(20), tau_rp(2)
{}

void Neuron::set_thresh_f()
{
	thresh_f = teta / (J * excit_connexions * tau);
}


