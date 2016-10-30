#include "Neuron.hpp"

Physics::Potential const Neuron::firing_threshold_= 20;
Physics::Potential const Neuron::rest_potential_= 10;
Physics::Time const Neuron::transmission_delay_= 1.5;
Physics::Time const Neuron::refactory_period_= 2;
Physics::Resistance const Neuron::membrane_resistance_= 5; ///< nbre qulconque
Physics::Amplitude const Neuron::amplitude_= 0.1;





Neuron::Neuron(bool const& exc, double const& eps, double const& ext_f)
: excitatory_(exc), inhib_connections_(250), excit_connections_(1000), epsilon_(eps), tau_(20), ext_f_(ext_f), t_(0)
{
    synapses_ = std::vector<Neuron*>(1250);
    std::priority_queue <Event> ev;
    events_in_ = ev;
    events_out_ = ev;
    // on initialise events_in_ et events_out_ à un tableau vide
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
    
    int nb_of_inputs (0);
    
    for (size_t i(0); i < synapses_.size(); ++i)
    {
        double X = t_ - synapses_[i]->get_t_output() - transmission_delay_; // ce qui nous intéresse c'est le temps auquel
        // l'autre neurone a output, puisqu'on regarde
        //si deltaT = D (transmission_delay_) et si c'est le cas I = J
        
        
        if(X == 0)    // Si X = 0, alors dirac(X) = 1 --> I =J
        {
            Event ev(t_, amplitude_);
            events_in_.push(ev);
            synapses_[i]->clear_top_output(); // indique que l'output de la synapse[i] a été utilisé donc doit
            // être sorti du tableau d'events_out_ de la synapse en question
            
            ++nb_of_inputs;
        }
        
    }
    
    Vm_ += (nb_of_inputs * amplitude_) / membrane_resistance_;
    
    // ici temporaire :creer une fonction qui met a jour la valeur du potentiel membranaire et l'appeler ici
    
    
}





// additionne tous les courants contenus dans les éléments de events_in_ ayant un t < t_ (notre attribut)
// pour ce faire on delete tous ces éléments un par un, après avoir incrémenté la valeur de leur courant
// à notre total (sum), qui va être retourné par la fonction en question
double Neuron::sum_events(double const& dt)
{
    double sum(0);
    
    while(events_in_.top().get_t() < (t_ + dt))
    {
        sum += events_in_.top().get_i();
        events_in_.pop();
    }
    
    return sum;
}







//Je trouve aussi cette méthode assez inutile vu qu'on pourrait juste invoquer tout ça dans update, mais à voir
void Neuron::output(double const& x)
{
    Event ev(t_, x);
    events_out_.push(ev);
}






bool Neuron::has_reached_threshold() const
{
    return Vm_ >= firing_threshold_;
}








// remet le potentiel de membrane au potentiel au repos, cette méthode sera appelée
// dans update si le threshold est dépassé
void Neuron::reset_potential()
{
    Vm_ = rest_potential_;
}









void Neuron::update(Physics::Time const& dt)
{
    
    input(dt); //met d'abord à jour les input
    
    
    // puis met à jour les output dans le cas où le threshold est atteint
    if (has_reached_threshold())
    {
        //output(X);
        output(sum_events(dt));
        reset_potential();
    }
    
}

// retourne le temps de l'output le plus ancien
double Neuron::get_t_output() const
{
    return events_out_.top().get_t();
}



//enlève l'output le plus ancien de events_out_ (à appeler que dans le cas où cet output a été utilisé)
void Neuron::clear_top_output()
{
    events_out_.pop();
}



void Neuron::set_connection(Neuron* neuron)
{
	synapses_.push_back(neuron);
}
	
	
	
