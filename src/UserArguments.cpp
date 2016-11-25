#include "UserArguments.hpp"

UserArguments::UserArguments(int argc, char** argv)
	try : cmd("Simulation of neurons network"),
	time_of_simulation_arg("t", "time","total simulation time", false, 1000, "double", cmd),
	number_neurons_arg("n", "neurons", "total number of neurons to consider for the simulation", false, 12500, "int", cmd),
	gamma_arg("g", "gamma", "proportion of inhibitory over excitatory neurons", false, 0.25, "double", cmd),
	epsilon_arg("e", "epsilon", "connections density", false, 0.1, "double", cmd),
	external_factor_arg("f", "factor", "external factor", false, 1, "double", cmd)
{
	cmd.parse(argc, argv);
}
 catch (TCLAP::ArgException& e)
{
	std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
}


UserArguments::~UserArguments()
{
}

double UserArguments::epsilon()
{
	return epsilon_arg.getValue();
}

double UserArguments::external_factor()
{
	return external_factor_arg.getValue();
}

double UserArguments::gamma()
{
	return gamma_arg.getValue();
}

Physics::Time UserArguments::time_of_simulation()
{
	return time_of_simulation_arg.getValue();
}

unsigned int UserArguments::number_neurons()
{
	return number_neurons_arg.getValue();
}
