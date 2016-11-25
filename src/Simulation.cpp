#include "Simulation.hpp"
#include <Physics.hpp>

Simulation::Simulation( unsigned int const number_neurons, Physics::Time const& time_of_simulation,
                        Physics::Time const& time_step, SimulationType const& type, //fixed step only arguments
                        double const gamma, double const epsilon,
                        double const& external_factor)
    : network_(type, number_neurons, gamma, epsilon, external_factor),
	time_of_simulation_(time_of_simulation),
	time_step_(time_step)
{
}

Simulation::Simulation( unsigned int const number_neurons, Physics::Time const& time_of_simulation,
                        double const gamma, double const epsilon,
                        double const& external_factor)
    : Simulation(number_neurons,time_of_simulation,-1,SimulationType::Analytic, gamma, epsilon, external_factor)
{
}

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
	while (network_.update(time_step_) < time_of_simulation_){};
}

