#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
    
    public :
    
    //constructeur et destructeur
    Neuron(bool const& exc, double const& eps, double const& ext_f);
    ~Neuron();
    
    
    //méthode publique
    void update(double const& dt); ///>adapt to chrono library
    
    //méthode inutiles
    //void add_event(double const& a_time, double const& a_current);
    //void spike();
    
    
    
    
    private :
    
    //méthodes privées
    bool has_reached_threshold() const;
    void input(double const& dt); ///>modifies current
    void output(double const& x); ///>modifies current
    void reset_potential(); ///>potential goes back to Vr
    double sum_events(double const& dt);
    double get_t_output() const;
    void clear_top_output();
    
    
    //attributs
    bool  const excitatory_;
    int const inhib_connections_; ///>number of connections from other inhibitatory neurons
    int const excit_connections_; ///>number of connections from other excitatory neurons
    double const epsilon_; ///>connection density
    double I_; ///>synaptic currents arriving at the soma
    double Vm_; ///>membrane potential
    double  const tau_; ///>time constant of the circuit
    double ext_f_; ///>external frequency
    
    double t_;
    std::priority_queue <Event> events_in_;
    std::priority_queue <Event> events_out_;
    std::vector <Neuron*> synapses_;
    
    static const Physics::Potential firing_threshold_;
    static const Physics::Potential rest_potential_; ///>Vr
    static const Physics::Time transmission_delay_; ///>D
    static const Physics::Time refactory_period_; ///>tau_rp
    static const Physics::Resistance membrane_resistance_; ///>R
    static const Physics::Amplitude amplitude_; ///>J
    
    
};


#endif
