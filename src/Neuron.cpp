#include "Neuron.hpp"
#include <cmath>

Physics::Potential const Neuron::firing_threshold_= 20;
Physics::Potential const Neuron::rest_potential_= 10;
Physics::Time const Neuron::transmission_delay_= 2; // vraie valeur est 1.5
Physics::Time const Neuron::tau_ = 20;
Physics::Amplitude const Neuron::amplitude_= 0.1;





Neuron::Neuron(Type const& a_type, bool const& exc, double const& eps,
				double const& ext_f, Physics::Resistance const& membrane_resistance)
: type_(a_type), excitatory_(exc), inhib_connections_(250), excit_connections_(1000),
 epsilon_(eps), ext_f_(ext_f), t_(0), membrane_resistance_(membrane_resistance)
{
    synapses_ = std::vector<Neuron*>(1250);
    std::priority_queue <Event> ev;
    events_in_ = ev; // on initialise events_in_ à un tableau vide

}





Neuron::~Neuron()
{
    for (auto& element : synapses_) {
        delete element;
        element = nullptr;
    }
    synapses_.clear();
}



double Neuron::get_Vm_()
{
	return Vm_;

}

double Neuron::get_I_() 
{
	return I_;
	
}


void Neuron::set_Vm_(double vm)
{
	Vm_ = vm; 
}


void Neuron::set_I_ (double current)
{
	I_= current;
	
}




void Neuron::input(Physics::Time const& dt)
{ 
	//ANALYTIC
	if(type_ == Type::Analytic)
	{
		//temps initial à partir duquel commence dt
		Physics::Time init_time (t_);
		
		//sélectionne chacun leur tour les évènements qui ont lieu avant la fin de dt
		while((events_in_.top().get_t() + transmission_delay_ < (init_time + dt)) && (refractory_period_ == 0))
		{
			//détermine le petit dt entre t_ et le moment auquel le spike arrive
			Physics::Time small_dt ( (events_in_.top().get_t() + transmission_delay_) - t_ );
			
			update_RI(small_dt);
			step(small_dt);
		}
		
	}
	
	else 
	{
		update_RI(dt);
		step(dt);
    }
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
    
    input(dt); //<met d'abord à jour les input (ce que le neurone reçoit)
    //<décrémenter refractory period jusqu'à 0 pas en dessous
    
    //< output à toutes ses connexions dans le cas où le threshold est atteint 
    //< et le courant estx remis à 0
    if (has_reached_threshold())
    {

        output(I_);
        reset_potential();
        I_ = 0;
        refractory_period_ = 2;
        
    }
    
}




void Neuron::set_connection(Neuron* neuron)
{
	synapses_.push_back(neuron);
}
	
void Neuron::step(Physics::Time const& dt) // faire en sorte que dans commandline on puisse entrer que 0,1,2
{
	
	switch(type_)
	{
		case Type::Analytic :
		step_analytic(dt);
		t_ = events_in_.top().get_t();
		break;
	 
		case Type::Explicit :
		step_explicit(dt);
		t_ += dt;
		break;
		
		case Type::Implicit :
		step_implicit(dt);
		t_ += dt;
		break;
	}
	
} 
	
	
void Neuron::step_analytic(Physics::Time const& dt)
{
	
	Vm_ = Vm_*exp(-dt/tau_) + membrane_resistance_*I_*(1-exp(-dt/tau_));
	
	
}


void Neuron::step_explicit(Physics::Time const& dt)// Use of V(t-1)=Vm_ to calculate the new Vm_
{
	Vm_ += ((-Vm_ + membrane_resistance_ * I_) * dt) / tau_;  
	
}


void Neuron::step_implicit(Physics::Time const& dt)
{
	Vm_ = ((dt * membrane_resistance_ * I_ ) + (tau_ * Vm_)) / ( dt + tau_); 
}


void Neuron::update_RI(Physics::Time const& dt)
{
	//ANALYTIC
	if(type_ == Type::Analytic)
	{
		
		I_ += events_in_.top().get_i();
		
		events_in_.pop();
		 

	}
	 
	else if ((type_ == Type::Explicit) or (type_ == Type::Implicit))
	{
		
		while((events_in_.top().get_t() < (t_ + dt)) && (refractory_period_ == 0))
		{
		// si la différence entre le temps courant et (transmission_delay_ + temps où le courant a été envoyé) = 0
		// la fonction de dirac retourne 1 et dans ce cas on incrémente le courant
			if (Physics::dirac_distribution(t_- transmission_delay_ - events_in_.top().get_t()) == 1)
			{
				I_ += amplitude_ / membrane_resistance_;
				events_in_.pop();
					
			}
	
		}	

	}
}
	
