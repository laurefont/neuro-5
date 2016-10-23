#include "Neuron.hpp"


Neuron::Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f, double const& time) : excitatory_(exc), inhib_connections_(250), excit_connections_(1000), epsilon_(eps), tau_(20), ext_f_(ext_f), firing_threshold_(20), rest_potential_(10),transmission_delay_(1.5), refactory_period_(2), amplitude_(0.1), t_(time)
{
	synapses_(1250, nullptr);
}

Neuron::~Neuron()
{
	for (auto& element : synapses_) {
		delete element;
		element = nullptr;
	}
	synapses_.clear();
}
	
	
void Neuron::add_event(double const& a_time, double const& a_current)
{
	Event e1(a_time, a_current);
	events_.push(e1);
}


void Neuron::input()
{
	for (size_t i(0); i < synapses_.size(); ++i)
	{
		double I_added(0);
		I_added = synapses_[i]->output() / membrane_resistance_; ///< en considérant que output est un V
		add_event(t_, I_added);
	}
}


double Neuron::sum_events() const
{
	double sum(0);
	
	for (size_t i(0); i < events_.size(); ++i)
	{
		sum += events_[i].get_i();
	}
	
	return sum;
}


double Neuron::output() const
{
	if (has_reached_threshold())
	{
		return sum_events(); 
	} else {
		return 0;
	}
}

		
void Neuron::spike()
{
	if (has_reached_threshold())
	{
		reset_potential();
		///< empty events
	}
}
		


bool Neuron::has_reached_threshold() const
{
	return sum_events() >= firing_threshold_;
}


void Neuron::reset_potential()
{ 
	V_ = rest_potential_;
}


void Neuron::update(double const& dt)
{
}

			
		
	
	
	
	
	
	
	
