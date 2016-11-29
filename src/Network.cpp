#include <Network.hpp>

#include <vector>
#include <memory>

#include <cmath>
#include <random>
#include <chrono>
#include <assert.h>

Network::Network(   SimulationType const& type, 
					unsigned int const& number_neurons,
					std::vector<unsigned int>* neuron_csv_files, 
					double const& gamma, 
					double const& epsilon, 
					double const& external_factor, 
					Physics::Potential firing_threshold,
					Physics::Time refractory_period, 
					Physics::Potential resting_potential,
					Physics::Potential reset_potential, 
					Physics::Time transmission_delay, 
					Physics::Time tau)
	: N_(number_neurons),
	  Ne_(std::round(N_ / (1 + gamma))),
	  Ni_(N_ - Ne_),
	  gamma_(gamma),
	  epsilon_(epsilon),
      type_(type)
{
	
	for (unsigned int i(0); i < N_; ++i)
	{
		for (size_t j(0); j < neuron_csv_files->size(); ++j)
		{
			neurons_.push_back(	std::unique_ptr<Neuron>(new Neuron(type, 
								(i < Ne_), firing_threshold, 
								refractory_period, resting_potential, 
								reset_potential, transmission_delay, 
								tau,  external_factor, 
								((*neuron_csv_files)[j] == i))));
		}
    }

	make_connections();
	
	raster_plot_file = new std::ofstream ("raster-plot.csv");
	if (raster_plot_file->fail()) 
	    throw std::runtime_error("file not found");
    else
        *raster_plot_file << "t,neuron" << std::endl;
 }

Network::~Network()
{
	raster_plot_file->close();
    delete raster_plot_file;
        
    for (auto& neuron : neurons_)
    {
		neuron = nullptr;
	}
	neurons_.clear();
}

Neuron* Network::get_neuron(unsigned int n)
{
    assert(n<=neurons_.size());
    return neurons_.at(n).get();
}

size_t Network::get_neurons_size()
{
    return neurons_.size();
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
                neuron->add_connection(potential_neuron_connected.get());
			}
		}
	}
}

Physics::Time Network::update(Physics::Time dt)
{
    if (type_ != SimulationType::Analytic) //Implicit or Explicit Solution
    {
	  for (unsigned int i(0); i< neurons_.size(); ++i)
	  {
		neurons_[i]->update(dt);
		if (neurons_[i]->has_reached_threshold())
			*raster_plot_file <<i <<"," << neurons_[i]->get_t() << std::endl;
	  }
      return neurons_[0]->get_t(); //time of the last neuron (send 0, all neurons have same time)
    }
    else //Analytic solution
    {
        Neuron_last last_neurons = get_last_neurons();
        int & last_id = last_neurons.last_id;
        int & second_last_id = last_neurons.second_last_id;

        //MAX step size for analytic solution is the next time where the
        //voltage may change. max step size that can be taken (if no event ahead):
        dt = neurons_[second_last_id]->get_t()
           + neurons_[second_last_id]->get_transmission_delay()
           - neurons_[last_id]->get_t();

        neurons_[last_id]->update(dt);
		if (neurons_[last_id]->has_reached_threshold())
			*raster_plot_file << last_id <<"," << neurons_[last_id]->get_t() << std::endl;
        return neurons_[second_last_id]->get_t(); //The 2nd last is now the last, return its time
	}
}


struct compare_neuron_time //used by get_back_neurons()
{
    inline bool operator() (const Neuron& n1, const Neuron& n2)
    {
        return (n1.get_t() < n2.get_t());
    }
};

Neuron_last Network::get_last_neurons()
{
    Neuron_last nl;
    nl.last_id=0;
    nl.second_last_id=0;
    for (unsigned int n=1; n<neurons_.size(); n++)
    {
        if (neurons_[n]->get_t() <= neurons_[nl.last_id]->get_t() )
        {
            nl.second_last_id = nl.last_id;
            nl.last_id = n;
        }
        else if (neurons_[n]->get_t() <= neurons_[nl.second_last_id]->get_t() )
        {
            nl.second_last_id = n;
        }
    }
    return nl;
}
