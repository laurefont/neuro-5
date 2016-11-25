#include "Simulation.hpp"
#include "UserArguments.hpp"

int main (int argc, char** argv)
{
	double time = -1;
	int  neurons = -1;
	
	UserArguments user_arguments(argc, argv);

	std::cout << "The number of neurons is : " << user_arguments.number_neurons() << std::endl;
	std::cout << "The simulation time is : " << user_arguments.time_of_simulation() << std::endl;

    Simulation sim(time, neurons);
    sim.launch_simulation();
}
