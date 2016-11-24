#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <fstream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


class Neuron {
    
  public :
    
    ///constructeur et destructeur
    Neuron(SimulationType const& a_type, bool const& exc, double const& external_factor=0.5);
            ///< constructor takes arguments that will be modified during time

    ~Neuron();
    
    //méthode publique
    bool has_reached_threshold() const;  ///< verify if Vm is >= thresold 
    void update(Physics::Time const& dt); ///< in a first step, the function updates inputs, then if the thresold is reached, the function update ouputs
    void add_connection(Neuron* neuron); ////< add outgoing synapse
    void step(Physics::Time const& dt); ///< performs a computation step
    void reset_potential(); ///< function reset the potential, it makes the potentiel return to the reset potential
    double get_Vm() const; ///< returns potential of neuron
    Physics::Time get_t() const;  ///<returns the time of the neuron
    void output(double const& x); ///< fires a spike to all post-synaptic neurons
    void add_event_in(Event const& ev); ///< add spike event to the queue of incoming spikes
    bool is_excitatory(); ///< true if excitatory, false if inhibitory
    int get_synapses_size() const; ///< number of outgoing synapses
    int get_event_in_size() const; ///< number of incoming spikes in queue
    Physics::Time get_transmission_delay() const; ///< returns transmission delay

    ///Clears queue of events between t and t+dt and returns the summed
    ///contribution of incoming currents
    Physics::Amplitude RI(Physics::Time const& dt);

    double external_spike_generator(Physics::Time const& dt);

    
  private:
    
    static unsigned int neuron_id_;
    std::ofstream * neuron_file; ///< output file for raster plot
    Physics::Amplitude J_; ///< synaptic weight of OUTGOING synapses
    Physics::Potential Vm_; ///< membrane potential
    Physics::Time t_; ///<time
    Physics::Time last_spike_time_; ///< Time of last firing
    std::priority_queue <Event> events_in_; ///<queue of input events 
    std::vector <Neuron*> synapses_; ///<table with the neurons it's sending signals to
    const double external_factor_;

    const SimulationType type_;
    static const Physics::Time refractory_period_; ///<tau_rp (period after an output, during which neuron can't receive inputs and can't fire)
    static const Physics::Potential firing_threshold_; ///<membrane potential level at which neuron fires
    static const Physics::Potential resting_potential_; ///<resting potential (voltage in equilibrium)
    static const Physics::Potential reset_potential_; ///< reset potential after the neuron has fired)
    static const Physics::Time transmission_delay_; ///<D (time taken by a signal after it's been produced to reach the receiving neuron)
    static const Physics::Time tau_; ///<Time constaint (tau)

    void step_analytic(Physics::Time const& dt); ///< analytic time-stepping solution
    void step_explicit(Physics::Time const& dt); ///< explicit time-stepping solution
    void step_implicit(Physics::Time const& dt); ///< implicit time-stepping solution
};


#endif
