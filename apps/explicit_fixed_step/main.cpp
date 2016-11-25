#include "Simulation.hpp"
#include "efsUserArguments.hpp"

#include <iostream>

int main (int argc, char** argv)
{
	efsUserArguments user_arguments(argc, argv);

	std::cout << "The number of neurons is : " << user_arguments.number_neurons() << std::endl;
	std::cout << "The simulation time is : " << user_arguments.time_of_simulation() << std::endl;
	std::cout << "The time step is : " << user_arguments.time_step() << std::endl;

	return 0;
}
