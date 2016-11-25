#include "Simulation.hpp"
#include "ifsUserArguments.hpp"

int main (int argc, char** argv)
{
	ifsUserArguments user_arguments(argc, argv);

	Simulation simulation(
						  user_arguments.number_neurons(), 
						  user_arguments.time_of_simulation(), 
						  user_arguments.time_step(), 
						  SimulationType::Implicit, 
						  user_arguments.gamma(), 
						  user_arguments.epsilon(), 
						  user_arguments.external_factor()
						  );

	simulation.launch_simulation();
		
	return 0;
}
