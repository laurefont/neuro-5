#include <SFML>
#include <iostream>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
	
	public :
    Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f);
    ~Neuron();
	
	void update(sf::Time dt); ///>adapt to chrono library
    bool has_reached_threshold();
    void input(sf::Time dt); ///>modifies current
    void output(sf::Time dt); ///>modifies current
    void reset_potential(); ///>potential goes back to Vr


	
	
	private :
	
    bool excitatory_;
	int inhib_connections_; ///>number of connections from other inhibitatory neurons
	int excit_connections_; ///>number of connections from other excitatory neurons
    double epsilon_; ///>connection density
    double I_; ///>synaptic currents arriving at the soma
	double V_; ///>membrane potential
	double tau_; ///>time constant of the circuit
	double ext_f_; ///>external frequency
    
    
    static const Physics::Potential firing_threshold_;
    static const Physics::Potential rest_potential_; ///>Vr
    static const Physics::Time transmission_delay_; ///>D
    static const Physics::Time refactory_period_; ///>tau_rp
    static const Physics::Resistance membrane_resistance_; ///>R
    static const Physics::Amplitude amplitude_ ///>J
    
	
};


#endif
