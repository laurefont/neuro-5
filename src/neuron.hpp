#include <SFML>
#include <iostream>


#ifndef NEURON_H
#define NEURON_H

class Neuron {
	
	public :
	Neuron();
	virtual ~Neuron(); //heritage ?
	
	void update(sf::Time dt);
	void set_thresh_f();
	
	
	private :
	
	int inhib_connexions; //number of connections from other inhibitatory neurons
	int excit_connexions; //number of connections from other excitatory neurons
	double I; //synaptic currents arriving at the soma
	double V; //membrane potential
	double Vr; //reset potential
	double R; //membrane resistance
	double D; //transmission delay
	double J; //amplitude
	double tau; //time constant of the circuit
	double tau_rp; //refractory period
	double teta; //firing threshold
	double thresh_f; //frequency that is needed for a neuron to reach threshold in absence of feedback
	double ext_f; //external frequency
	bool has_reached_threshold;
	
};


#endif
