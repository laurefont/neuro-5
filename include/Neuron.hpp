#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


class Neuron {
    
    public :
    
    //constructeur et destructeur
    Neuron(Type const& a_type, bool const& exc, double const& eps,
			double const& ext_f, Physics::Resistance const& membrane_resistance); ///< constructor takes arguments that will be modified during time 
 

    ~Neuron();
    
    
    //méthode publique
    void update(Physics::Time const& dt); ///< in a first step, the function updates inputs, then if the thresold is reached, the function update ouputs
    void set_connection(Neuron* neuron);
    void step(Physics::Time const& dt); // à peut-être mettre en privé
    void step_analytic(Physics::Time const& dt);
    void step_explicit(Physics::Time const& dt); ///< explicit time-stopping solution
    void step_implicit(Physics::Time const& dt);
    void update_RI(Physics::Time const& dt);
    double get_Vm_(); 
    double get_I_(); 
    void set_Vm_(double vm); 
    void set_I_ (double current); 
   
    private :
    
    //méthodes privées
    bool has_reached_threshold() const;  ///< verify if Vm is >= thresold 
    void input(Physics::Time const& dt); ///< uses function of dirac to know if the current has been added and updates Vm
    void output(double const& x); ///< updates the output
    void reset_potential(); ///< function reset the potential, it makes the potentiel return to the state potential
    void add_event_in(Event const& ev);
    
    
    //attributs
    Type type_;
    bool  const excitatory_; ///<true if neuron excitatory OR false if neuron inhibatory
    int const inhib_connections_; ///<number of connections from other inhibitatory neurons
    int const excit_connections_; ///<number of connections from other excitatory neurons
    double const epsilon_; ///<connection density
    double I_; ///<synaptic currents arriving at the soma
    Physics::Potential Vm_; ///<membrane potential
    Physics::Time refractory_period_; ///<tau_rp (period after an output, during which neuron can't receive inputs and can't fire)
    Physics::Time t_; ///<time
    std::priority_queue <Event> events_in_; ///<queue of input events 
    std::vector <Neuron*> synapses_; ///<table with the neurons it's sending signals to
    
    static const Physics::Potential firing_threshold_; ///<membrane potential level at which neuron fires
    static const Physics::Potential rest_potential_; ///<Vr (reset potential after the neuron has fired)
    static const Physics::Time transmission_delay_; ///<D (time taken by a signal after it's been produced to reach the receiving neuron)
    static const Physics::Amplitude amplitude_; ///<J (amplitude of an input)
    static Physics::Time const tau_; ///<time constant of the circuit
    
    const Physics::Resistance membrane_resistance_; ///<R (resistance of the membrane)
    const Physics::Frequency ext_f_;
    
};


#endif
