#include "Neuron.hpp"

Physics::Potential const Neuron::firing_threshold_= 20;
Physics::Potential const Neuron::rest_potential_= 10;
Physics::Time const Neuron::transmission_delay_= 1.5;
Physics::Time const Neuron::refactory_period_= 2;
Physics::Resistance const Neuron::membrane_resistance_= 5; ///< nbre qulconque
Physics::Amplitude const Neuron::amplitude_= 0.1;


Neuron::Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f, double const& time) : excitatory_(exc), inhib_connections_(250), excit_connections_(1000), epsilon_(eps), tau_(20), ext_f_(ext_f), t_(0)
{
	synapses_ = std::vector<Neuron*>(1250);
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


double Neuron::sum_events(double const& dt) const
{
	double sum(0);
	
	while(events_.top().get_t() < (t_ + dt))
	{
		sum += events_.top().get_i();
		events_.pop();
	}
	
	return sum;
}


double Neuron::output(double const& dt) const
{
	if (has_reached_threshold())
	{
		return sum_events(dt); 
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

			
		
	
	
	
	
	
	
	
