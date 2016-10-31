#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


class Neuron {
    
    public :
    
    //constructeur et destructeur
    Neuron(bool const& exc, double const& eps, double const& ext_f);
    ~Neuron();
    
    
    //méthode publique
    void update(Physics::Time const& dt);
    void set_connection(Neuron* neuron);
    
    
    
   
    private :
    
    //méthodes privées
    bool has_reached_threshold() const;
    void input(Physics::Time const& dt); ///<modifies current
    void output(double const& x); ///<modifies current
    void reset_potential(); ///<potential goes back to Vr
    double sum_events(Physics::Time const& dt);
    double get_t_output() const;
    void clear_top_output();
    
    
    //attributs
    bool  const excitatory_; ///<true if neuron excitatory OR false if neuron inhibatory
    int const inhib_connections_; ///<number of connections from other inhibitatory neurons
    int const excit_connections_; ///<number of connections from other excitatory neurons
    double const epsilon_; ///<connection density
    double I_; ///<synaptic currents arriving at the soma
    double Vm_; ///<membrane potential
    double  const tau_; ///<time constant of the circuit
    double ext_f_; ///<external frequency
    
    Physics::Time t_; ///<time
    std::priority_queue <Event> events_in_; ///<queue of input events 
    std::priority_queue <Event> events_out_; ///<queue of output events
    std::vector <Neuron*> synapses_; ///<table with the neurons it's sending signals to
    
    static const Physics::Potential firing_threshold_; ///<membrane potential level at which neuron fires
    static const Physics::Potential rest_potential_; ///<Vr (reset potential after the neuron has fired)
    static const Physics::Time transmission_delay_; ///<D (time taken by a signal after it's been produced to reach the receiving neuron)
    static const Physics::Time refactory_period_; ///<tau_rp (period after an output, during which neuron can't receive inputs and can't fire)
    static const Physics::Resistance membrane_resistance_; ///<R (resistance of the membrane)
    static const Physics::Amplitude amplitude_; ///<J (amplitude of an input)
    
    
};


#endif
