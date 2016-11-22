#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <fstream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


class Neuron {
    
    public :
    
    //constructeur et destructeur
    Neuron(Type const& a_type, bool const& exc, double const& external_factor=0.5);
            ///< constructor takes arguments that will be modified during time

    ~Neuron();
    
    
    //méthode publique
    bool has_reached_threshold() const;  ///< verify if Vm is >= thresold 
    void update(Physics::Time const& dt); ///< in a first step, the function updates inputs, then if the thresold is reached, the function update ouputs
    void set_connection(Neuron* neuron);
    void step(Physics::Time const& dt); // à peut-être mettre en privé
    void step_analytic(Physics::Time const& dt);
    void step_explicit(Physics::Time const& dt); ///< explicit time-stopping solution
    void step_implicit(Physics::Time const& dt);
    void update_RI(Physics::Time const& dt);
    void reset_potential(); ///< function reset the potential, it makes the potentiel return to the state potential
    double get_Vm() const; 
    double get_I() const; 
    Physics::Time get_t() const;	///<returns the time of the neuron
    void input(Physics::Time const& dt); ///< uses function of dirac to know if the current has been added and updates Vm
    void output(double const& x); ///< fires a spike to all post-synaptic neurons
    void add_event_in(Event const& ev);
    int get_synapses_size() const;
    int get_event_in_size() const;
    double external_spike_generator(Physics::Time const& dt); 
    
    private:
    
    //attributs
    Type type_;
    static unsigned int neuron_id_;
    std::ofstream * neuron_file; ///< output file for raster plot
    bool const excitatory_; ///<true if neuron excitatory OR false if neuron inhibatory
    double J_; ///<synaptic weight
    Physics::Potential Vm_; ///<membrane potential
    Physics::Time t_; ///<time
    Physics::Time last_spike_time_; ///< Time of last firing
    std::priority_queue <Event> events_in_; ///<queue of input events 
    std::vector <Neuron*> synapses_; ///<table with the neurons it's sending signals to
    const double external_factor_;

    static const Physics::Time refractory_period_; ///<tau_rp (period after an output, during which neuron can't receive inputs and can't fire)
    static const Physics::Potential firing_threshold_; ///<membrane potential level at which neuron fires
    static const Physics::Potential resting_potential_; ///<resting potential (voltage in equilibrium)
    static const Physics::Potential reset_potential_; ///< reset potential after the neuron has fired)
    static const Physics::Time transmission_delay_; ///<D (time taken by a signal after it's been produced to reach the receiving neuron)
    static const Physics::Amplitude amplitude_; ///<J (amplitude of an input)
    static Physics::Time const tau_; ///<time constant of the circuit
    static const Physics::Resistance membrane_resistance_; ///<R (resistance of the membrane)
};


#endif
