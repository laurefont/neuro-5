#include <Network.hpp>

#include <vector>
#include <memory>
#include <set>
#include <algorithm>

#include <cmath>
#include <random>
#include <chrono>
#include <assert.h>

Network::Network(   SimulationType const& type, 
					unsigned int const& number_neurons,
					bool const& add_external_current,
                    std::vector<unsigned int>* output_neuron_ids,
					double const& gamma, 
					double const& epsilon, 
					double const& external_factor, 
					unsigned random_seed,
					Physics::Potential firing_threshold,
					Physics::Time refractory_period, 
					Physics::Potential resting_potential,
					Physics::Potential reset_potential, 
					Physics::Time transmission_delay, 
					Physics::Time tau,
					Physics::Time time_of_simulation) 
					
	: N_(number_neurons),
	  Ne_(std::round(N_ / (1 + gamma))),
	  Ni_(N_ - Ne_),
	  gamma_(gamma),
	  epsilon_(epsilon),
      type_(type)
{
    std::cout << "Creating " << N_ << " neurons..." << std::endl;
    neurons_ = new Neuron*[number_neurons];
	for (unsigned int i(0); i < N_; ++i)
	{
        bool output =  output_neuron_ids != NULL //not empty
                    && std::find(output_neuron_ids->begin(), output_neuron_ids->end(), i) != output_neuron_ids->end();
        neurons_[i] = new Neuron(type, (i < Ne_), add_external_current,
                                firing_threshold, time_of_simulation,
                                refractory_period, resting_potential,
                                reset_potential, transmission_delay,
                                tau,  external_factor, random_seed, output, i);
    }

    std::cout << "Creating " << epsilon_*100 << "\% network connectivity (random seed " << random_seed << ")..." << std::endl;
    make_connections(random_seed);
	
	spike_times_ = new unsigned int[time_of_simulation]();
    raster_plot_file = new std::ofstream ("raster_plot.csv");
	if (raster_plot_file->fail()) 
	    throw std::runtime_error("file not found");
    else
        *raster_plot_file << "t,neuron" << std::endl;
        
    spike_file = new std::ofstream ("firing_rate.csv");
    if  (spike_file->fail()) 
	    throw std::runtime_error("file not found");
    else
        *spike_file << "t,spikes" << std::endl;
 }

Network::~Network()
{
	raster_plot_file->close();
    delete raster_plot_file;
    
    spike_file->close();
    delete spike_file;

    for (unsigned int i=0; i<N_; i++)
        delete neurons_[i];
        
    delete[] neurons_;
    
    if(spike_times_) ///> True if spike_times_ is not a null pointer
        delete[] spike_times_;
}

Neuron* Network::get_neuron(unsigned int n)
{
    assert(n<=N_);
    return neurons_[n];
}

void Network::make_connections(unsigned seed)
{
	// Construct a random generator engine from a time-based seed
	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Use a bernoulli distribution with a epsilon_ chance of success
	std::bernoulli_distribution distribution(epsilon_);

    for (unsigned int n1 = 0; n1<N_; n1++)
    {
        Neuron * neuron = get_neuron(n1);
        for (unsigned int n2 = 0; n2<N_; n2++)
        {
            Neuron * potential_neuron_connected = get_neuron(n2);

			// Checks that it's not connecting to itself and
			// if it has the chance to connect to potential_neuron_connected
            if (n1 != n2 && distribution(generator))
			{
				// Do not release ownership of the pointer
                neuron->add_connection(potential_neuron_connected);
			}
		}
	}
}

Physics::Time Network::update(Physics::Time dt)
{
    if (type_ != SimulationType::AnalyticVariableStep) //Fixed Step methods
    {
      for (unsigned int i=0; i< N_; ++i)
	  {
        bool has_reached_threshold = neurons_[i]->update(dt);
        if (has_reached_threshold)
			{
            *raster_plot_file << neurons_[i]->get_t() <<"," << i << std::endl;
            ++spike_times_[(int)neurons_[i]->get_t()];
			}
	  }
      return neurons_[0]->get_t(); //time of the last neuron (send 0, all neurons have same time)
    }
    else //Analytic variable-step solution
    {
        Neuron_last last_neurons = get_last_neurons();
        int & last_id = last_neurons.last_id;
        int & second_last_id = last_neurons.second_last_id;

        //MAX step size for analytic solution is the next time where the
        //voltage may change. max step size that can be taken (if no event ahead):
        dt = neurons_[second_last_id]->get_t()
           + neurons_[second_last_id]->get_transmission_delay()
           - neurons_[last_id]->get_t();

        Neuron * last_neuron = neurons_[last_id];
        bool has_reached_threshold = last_neuron->update(dt);
        if (has_reached_threshold) 
			{
				*raster_plot_file << last_neuron->get_t() <<"," << last_neuron->get_neuron_id() << std::endl;
				++spike_times_[(int)last_neuron->get_t()];
			}
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
    for (unsigned int n=1; n<N_; n++)
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

void Network::write_spikes_to_file(unsigned int const& t)
{
    if (spike_file)
		{
			for (size_t i(0); i < t; ++i)
				*spike_file << i << "," << spike_times_[i] << std::endl;
				
		}
}
