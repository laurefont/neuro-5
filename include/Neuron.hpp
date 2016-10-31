#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
    
    public :
    
    //constructeur et destructeur
    Neuron(bool const& exc, double const& eps, double const& ext_f); ///> constructor takes arguments that will be modified during time 
																	///> other arguments like tau, tau,t_, inhib_connections and excit_connections have a fixed value in the cpp 
                                                                   ///> dans le corps du constructeur, we initialize events_in_ and events_out_ to an empty queue

    ~Neuron(); ///> destructor delete all the pointers of synapse table
		
    //méthode publique
    void update(double const& dt); ///> in a first step, the function updates inputs, then if the thresold is reached, the function update ouputs
    
    //méthode inutiles
    //void add_event(double const& a_time, double const& a_current);
    //void spike();
    
    
    
    
    private :
    
    //méthodes privées
    bool has_reached_threshold() const; ///> verify if Vm is >= thresold 
    void input(double const& dt); ///>uses function of dirac to know if the current has been added and updates Vm
    void output(double const& x); ///> updates the output
    void reset_potential(); ///> function reset the potential, it makes the potentiel return to the state potential
    double sum_events(double const& dt); ///> sum all the currents contained in elements of events_in with a t < t_, to do that we delete all these elements one by one, after having incremented the value of their current
										 ///>to our total (sum), which will be returned by the function in question
    double get_t_output() const; ///>return the time of the older output, it could be used to a neuron find at which time another neuron send him a signal 
								///>(the neuron will find on the queue the output that the other one send to him --> for himself it's the input)
    void clear_top_output(); ///>function that remove the older output on the queue events_out, so the one that arrives first
							 ///> (to use only in the case that the output has been used
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
