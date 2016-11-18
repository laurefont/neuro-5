#include <tclap/CmdLine.h>
#include "Simulation.hpp"

int main (int argc, char** argv)
{
	try {

		TCLAP::CmdLine cmd("Simulation of neurons network", ' ', "0.9");

		TCLAP::ValueArg<Physics::Time> time_of_simulation_arg("t", "time","total simulation time", false, 1000, "double", cmd);
		TCLAP::ValueArg<Physics::Time> time_step_arg("d", "dt", "time step of the simulation", false, 2, "Time", cmd);
		TCLAP::ValueArg<unsigned int> number_nneurons_arg("n", "neurons", "total number of neurons to consider for the simulation", false, 12500, "int", cmd); 
		TCLAP::ValueArg<double> gamma_arg("g", "gamma", "proportion of inhibitory over excitatory neurons", false, 0.25, "double", cmd);
		TCLAP::ValueArg<double> epsilon_arg("e", "epsilon", "connections density", false, 0.1, "double", cmd);
		TCLAP::ValueArg<Physics::Resistance> membrane_resistance_arg("r", "resistance", "resistance of the membrane", false, 1, "Resistance", cmd);
		TCLAP::ValueArg<Physics::Frequency> external_frequency_arg("f", "frequency", "external frequency", false, 1, "Frequency", cmd);

		cmd.parse(argc, argv);

		const Physics::Time time_of_simulation {time_of_simulation_arg.getValue()};
		const Physics::Time time_step {time_step_arg.getValue()};
		const unsigned int number_neurons {number_nneurons_arg.getValue()};
		const double gamma {gamma_arg.getValue()};
		const double epsilon {epsilon_arg.getValue()};
		const Physics::Resistance membrane_resistance {membrane_resistance_arg.getValue()};
		const Physics::Frequency external_frequency {external_frequency_arg.getValue()};

		// TODO fix simulation
		//Simulation simulation(time_of_simulation, time_step, Type::Implicit, number_neurons, gamma, epsilon, membrane_resistance, external_frequency);
		//simulation.launch_simulation();

	} catch (TCLAP::ArgException& e) {
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
