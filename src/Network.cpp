#include <Network.hpp>

#include <cmath>
#include <random>
#include <chrono>

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
	// Construct a random generator engine from a time-based seed
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Use a uniform distribution of numbers between 1 and 100
	std::uniform_int_distribution<int> distribution(1,100);

	for (auto& neuron : neurons_)
	{
		for (auto& potential_neuron_connected : neurons_)
		{
			// Checks that it's not connecting to itself
			if (&neuron != &potential_neuron_connected)
			{
				// epsilon_ chance of connecting to neuron_connected
				bool do_connection (distribution(generator) <= epsilon_ * 100);
				if (do_connection)
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

