#include <SFML>
#include <iostream>
#include "neuron.hpp"


#ifndef NETWORK_H
#define NETWORK_H

class Network {
	
	public :
	Network();
	~Network();
	
	void update(sf::Time dt);
	
	private :
	int N; //total number of neurons
	int Ne; //number of excitatory neurons
	int Ni; //number of inhibitatory neurons
	std::vector <Neuron*> neurons;
	
};

#endif
