#include "Neuron.hpp"

Physics::Potential const Neuron::firing_threshold_= 20;
Physics::Potential const Neuron::rest_potential_= 10;
Physics::Time const Neuron::transmission_delay_= 2; ///< vraie valeur est 1.5
Physics::Time const Neuron::refactory_period_= 2;
Physics::Resistance const Neuron::membrane_resistance_= 5; ///< nbre qulconque
Physics::Amplitude const Neuron::amplitude_= 0.1;





Neuron::Neuron(bool const& exc, double const& eps, double const& ext_f)
: excitatory_(exc), inhib_connections_(250), excit_connections_(1000), epsilon_(eps), tau_(20), ext_f_(ext_f), t_(0)
{
    synapses_ = std::vector<Neuron*>(1250);
    std::priority_queue <Event> ev;
    events_in_ = ev;
    // on initialise events_in_ à un tableau vide
}





Neuron::~Neuron()
{
    for (auto& element : synapses_) {
        delete element;
        element = nullptr;
    }
    synapses_.clear();
}





void Neuron::input(Physics::Time const& dt)
{ 

	
	while((events_in_.top().get_t() < (t_ + dt)) && (refractory_period_ == 0))
	{
		// si la différence entre le temps courant et (transmission_delay_ + temps où le courant a été envoyé) = 0
		// la fonction de dirac retourne 1 et dans ce cas on incrémente le courant
		if (Physics::dirac_distribution(t_- transmission_delay_ - events_in_.top().get_t()) == 1)
		{
			I_ += amplitude_;
			events_in_.pop();
					
		}
	
	}	
	 
	Vm_ += -(Vm_ - membrane_resistance_ * I_) / tau_;  ///< equation
    
}



void Neuron::output(double const& x)
{

    Event ev(t_, x);
    
    for (size_t i(0); i < synapses_.size(); ++i)
    {
		synapses_[i]->add_event_in(ev);
	}
}




bool Neuron::has_reached_threshold() const
{
    return Vm_ >= firing_threshold_;
}


void Neuron::add_event_in(Event const& ev)
{
	events_in_.push(ev);
}





// remet le potentiel de membrane au potentiel au repos, cette méthode sera appelée
// dans update si le threshold est dépassé
void Neuron::reset_potential()
{
    Vm_ = rest_potential_;
}





void Neuron::update(Physics::Time const& dt)
{
    
    input(dt); //met d'abord à jour les input (ce que le neurone reçoit)
    //décrémenter refractory period jusqu'à 0 pas en dessous
    
    // output à toutes ses connexions dans le cas où le threshold est atteint 
    // et le courant est remis à 0
    if (has_reached_threshold())
    {

        output(I_);
        reset_potential();
        I_ = 0;
        //mettre refractory period au max
        
    }
    
}




void Neuron::set_connection(Neuron* neuron)
{
	synapses_.push_back(neuron);
}
	
	
	
