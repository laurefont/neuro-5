#include "Simulation.hpp"



Simulation::Simulation(Physics:Time const& time_of_simulation) 
{
	
}
 
Simulation(Physics:Time const& time_of_simulation, Type const& type,
			Physics:Time const& time_step,
			Physics::Resistance const& resistance)
{
	
}

void Simulation::launch_simulation()
{
	do {
		network_.update(time_step_);
		time_of_simulation_ -= time_step_;
		///> update plot

	} while(time_of_simulation_ >= 0);
	
}

