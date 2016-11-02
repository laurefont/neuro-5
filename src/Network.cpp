#include <Network.hpp>

#include <cmath>

#include <cstdlib>

#include <ctime>

#include <Physics.hpp>

Network::Network(unsigned int const number_neurons, double const gamma, double const epsilon, double const g)
	: N_(number_neurons),
	  Ne_(std::round(N_ / (1 + gamma))),
	  Ni_(N_ - Ne_),
	  gamma_(gamma),
	  epsilon_(epsilon),
	  g_(g)
{
}

Network::~Network()
{
}

void Network::make_connections()
{
	//intitializes rand()
	srand(time(NULL));
		
	for(auto& neuron : neurons_)
	{
		for(auto& potential_neuron_connected : neurons_)
		{
			//checks that it's not connecting to itself
			if(&neuron != &potential_neuron_connected)
			{
				//10% chance of connecting to neuron_connected
				bool do_connection ( (rand()%100) < 10)
				
				
				if(do_connection)
				{
					neuron.set_connection(&potential_neuron_connected);
				}
			}
		}
	}
}

void Network::update(Physics::Time dt)
{
}

