#include <Network.hpp>

#include <vector>
#include <memory>

#include <cmath>
#include <random>
#include <chrono>

#include <Physics.hpp>

Network::Network(Type const type, unsigned int const number_neurons, double const gamma, double const epsilon, Physics::Frequency const ext_f, Physics::Resistance const membrane_resistance)
	: N_(number_neurons),
	  Ne_(std::round(N_ / (1 + gamma))),
	  Ni_(N_ - Ne_),
	  gamma_(gamma),
	  epsilon_(epsilon)
{
	for (unsigned int i(0); i < Ne_; ++i) {
		neurons_.push_back(std::unique_ptr<Neuron>(new Neuron(type, true, epsilon_, ext_f, membrane_resistance)));
	}

	for (unsigned int i(0); i < Ni_; ++i) {
		neurons_.push_back(std::unique_ptr<Neuron>(new Neuron(type, false, epsilon_, ext_f, membrane_resistance)));
	}

	make_connections();
}

Network::~Network()
{
}

void Network::make_connections()
{
	// Construct a random generator engine from a time-based seed
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Use a bernoulli distribution with a epsilon_ chance of success
	std::bernoulli_distribution distribution(epsilon_);

	for (auto& neuron : neurons_)
	{
		for (auto& potential_neuron_connected : neurons_)
		{
			// Checks that it's not connecting to itself and
			// if it has the chance to connect to potential_neuron_connected
			if (neuron != potential_neuron_connected && distribution(generator))
			{
				// Do not release ownership of the pointer
				neuron->set_connection(potential_neuron_connected.get());
			}
		}
	}
}

void Network::update(Physics::Time dt)
{
	for (auto& neuron : neurons_)
	{
		neuron->update(dt);
	}
}

