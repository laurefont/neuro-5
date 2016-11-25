#include "efsUserArguments.hpp"

efsUserArguments::efsUserArguments(int argc, char** argv)
	try : UserArguments(argc, argv),
	time_step_arg("d", "dt", "time step of the simulation", false, 2, "Time", cmd)
{
	cmd.parse(argc, argv);
}
 catch (TCLAP::ArgException& e)
{
	std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
}

efsUserArguments::~efsUserArguments()
{
}

Physics::Time efsUserArguments::time_step()
{
	return time_step_arg.getValue();
}

