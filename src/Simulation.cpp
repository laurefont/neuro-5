#include "Simulation.hpp"

Simulation::Simulation( unsigned int const number_neurons, 
						Physics::Time const& time_of_simulation,
                        Physics::Time const& time_step, 
                        SimulationType const& type, //fixed step only arguments
                        bool const& add_external_current,
                        std::vector<unsigned int>* neuron_csv_files,
                        Physics::Potential firing_threshold,
						Physics::Time refractory_period,
						Physics::Potential resting_potential,
						Physics::Potential reset_potential,
						Physics::Time transmission_delay,
						Physics::Time tau,
						double const gamma, double const epsilon,
						double const& external_factor,
						unsigned random_seed,
						Physics::Time spike_interval)
						
						: network_(type, number_neurons, 
							add_external_current, neuron_csv_files, 
							gamma, epsilon, external_factor, 
							random_seed, firing_threshold, 
							refractory_period, resting_potential, 
							reset_potential, transmission_delay, 
							tau, time_of_simulation, spike_interval),
						time_of_simulation_(time_of_simulation),
						time_step_(time_step)
{}


Simulation::Simulation( unsigned int const number_neurons, 
						Physics::Time const& time_of_simulation,
						bool const& add_external_current,
						std::vector<unsigned int>* neuron_csv_files,
                        Physics::Potential firing_threshold,
                        Physics::Time refractory_period,
                        Physics::Potential resting_potential,
                        Physics::Potential reset_potential,
                        Physics::Time transmission_delay,
                        Physics::Time tau,
                        double const gamma, 
                        double const epsilon,
                        double const& external_factor,
                        unsigned random_seed,
                        Physics::Time spike_interval )

		: Simulation(   number_neurons,
						time_of_simulation,  
						-1,
                        SimulationType::AnalyticVariableStep,
						add_external_current,
						neuron_csv_files,
						firing_threshold, 
						refractory_period, 
						resting_potential,
						reset_potential, 
						transmission_delay, 
						tau, 
						gamma, 
						epsilon,
						external_factor,
						spike_interval)
{}


Simulation::~Simulation(){}

Network* Simulation::get_network()
{
    return &network_;
}

Physics::Time Simulation::get_simulation_time()
{
    return time_of_simulation_;
}


void Simulation::launch_simulation()
{
    std::cout << "Running simulation for " << time_of_simulation_ << " ms..." << std::endl;
    while (network_.update(time_step_) < time_of_simulation_){};
    network_.write_spikes_to_file();
}

