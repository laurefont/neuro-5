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
	
	flow = std::ofstream ("raster-plot.csv");
}

Network::~Network()
{
	flow.close();
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
	//for (auto& neuron : neurons_)
	for (unsigned int i(0); i< neurons_.size(); ++i)
	{
		neurons_[i]->update(dt);
		if (neurons_[i]->has_reached_threshold())
		{
			if (flow.fail()) 
			{
				throw std::runtime_error("file not found");
			}
			else
			{
				flow <<i <<"," << neurons_[i]->get_t_() << std::endl;
			}
			
		}
	}
	
}



Neuron_last Network::get_back_neuron()
{
	int index(0);
	int index_very_last(0);
	
	//renvoie le neuron qui est le plus en arrière dans le temps
	Physics::Time time_very_last(neurons_[0]->get_t());
	
	//renvoie le neuron qui est l'avant dernier dans le temps
	Physics::Time time_almost_last(neurons_[1]->get_t());
	
	for(auto& neuron : neurons_)
	{
		if(neuron->get_t() < time_very_last)
		{
			time_almost_last = time_very_last;
			time_very_last = neuron->get_t();
			index_very_last = index;
			
		}
		
		++index;
		
	}
	
	Neuron_last x;
	x.very_last = index_very_last;
	x.almost_last_time = time_almost_last;
	
	return x;
	
}
