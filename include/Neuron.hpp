#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
	
	public :
    Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f, double const& time);
    ~Neuron();
	
	void update(double const& dt); ///>adapt to chrono library
    bool has_reached_threshold() const;
    void input(); ///>modifies current
    double output(double const & dt) const; ///>modifies current
    void reset_potential(); ///>potential goes back to Vr
	void add_event(double const& a_time, double const& a_current);
	double sum_events(double const& dt) const;
	void spike();
	

	
	
	private :
	
    bool excitatory_;
	int inhib_connections_; ///>number of connections from other inhibitatory neurons
	int excit_connections_; ///>number of connections from other excitatory neurons
    double epsilon_; ///>connection density
    double I_; ///>synaptic currents arriving at the soma
	double V_; ///>membrane potential
	double tau_; ///>time constant of the circuit
	double ext_f_; ///>external frequency
    
    double t_;
	std::priority_queue <Event> events_;
	std::vector <Neuron*> synapses_;
    
    static const Physics::Potential firing_threshold_;
    static const Physics::Potential rest_potential_; ///>Vr
    static const Physics::Time transmission_delay_; ///>D
    static const Physics::Time refactory_period_; ///>tau_rp
    static const Physics::Resistance membrane_resistance_; ///>R
    static const Physics::Amplitude amplitude_; ///>J
    
	
};


#endif
