#include "Simulation.hpp"
#include <Physics.hpp>

Simulation::Simulation(Physics::Time const& time_of_simulation, Physics::Time const& time_step, Type const& type,
					unsigned int const number_neurons, double const gamma, double const epsilon,
                    Physics::Resistance const& membrane_resistance, double const& external_factor,
                    Physics::Time refractory_period_)
    : network_(type, number_neurons, gamma, epsilon, membrane_resistance, external_factor, refractory_period_),
	time_of_simulation_(time_of_simulation),
	time_step_(time_step)
{
}

Simulation::Simulation(Physics::Time const& time_of_simulation, unsigned int const number_neurons,
					double const gamma, double const epsilon, Physics::Resistance const& membrane_resistance,
                    double const& external_factor, Physics::Time refractory_period_)
    : Simulation(time_of_simulation, 1, Type::Analytic, number_neurons, gamma, epsilon, membrane_resistance, external_factor, refractory_period_)
{
}

Simulation::~Simulation(){}

void Simulation::launch_simulation()
{
	while (network_.update(time_step_) < time_of_simulation_){};
}

