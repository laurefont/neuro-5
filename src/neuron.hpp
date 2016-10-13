#include <SFML>
#include <iostream>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
	
	public :
	Neuron(); ///add arguments
	virtual ~Neuron(); ///heritage ?
	
	void update(sf::Time dt); ///adapt to chrono library
    bool has_reached_threshold();
    void input(sf::Time dt); ///modifies current
    void output(sf::Time dt); ///modifies current
    
    
    

	
	
	private :
	
    bool excitatory_;
	int inhib_connections_; ///number of connections from other inhibitatory neurons
	int excit_connections_; ///number of connections from other excitatory neurons
    double epsilon_; ///connection density
    double I_; ///synaptic currents arriving at the soma
	double V_; ///membrane potential
	double tau_; ///time constant of the circuit
	double tau_rp_; ///refractory period
	double ext_f_; ///external frequency
    
    static const Physics::Potential firing_threshold_;
    static const Physics::Potential rest_potential_; ///Vr
    static const Physics::Time transmission_delay_; ///D
    static const Physics::Time refactory_period_;
    static const Physics::Resistance membrane_resistance_; ///R
    static const Physics::Amplitude amplitude_ ///J
    
	
};


#endif
