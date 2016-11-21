#include "Simulation.hpp"
#include <Physics.hpp>

Simulation::Simulation(Physics::Time const& time_of_simulation, Physics::Time const& time_step, Type const& type,
					unsigned int const number_neurons, double const gamma, double const epsilon,
					Physics::Resistance const& membrane_resistance, Physics::Frequency ext_f)
	: network_(type, number_neurons, gamma, epsilon, membrane_resistance, ext_f),
	time_of_simulation_(time_of_simulation), time_step_(time_step)
{
}

Simulation::Simulation(Physics::Time const& time_of_simulation, unsigned int const number_neurons,
					double const gamma, double const epsilon, Physics::Resistance const& membrane_resistance,
					Physics::Frequency ext_f)
	: Simulation(time_of_simulation, 0, Type::Analytic, number_neurons, gamma, epsilon, membrane_resistance, ext_f)
{
}

Simulation::~Simulation(){}

void Simulation::launch_simulation()
{
	while (network_.update(time_step_) < time_of_simulation_);
}

