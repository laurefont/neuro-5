#include "Simulation.hpp"

int main (int argc, char** argv)
{
    UserArguments user_arguments(argc, argv);

	Simulation simulation(
                          user_arguments.get_number_neurons(),
                          user_arguments.get_time_of_simulation(),
                          user_arguments.get_time_step(),
						  SimulationType::Implicit, 
                          user_arguments.get_gamma(),
                          user_arguments.get_epsilon(),
                          user_arguments.get_external_factor()
						  );

	simulation.launch_simulation();
		
	return 0;
}
