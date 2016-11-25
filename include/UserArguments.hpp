#include <tclap/CmdLine.h>

#include <Simulation.hpp>

///
/// @brief Common user arguments parser
///
class UserArguments
{
public:
    UserArguments(int argc, char** argv);
    virtual ~UserArguments();

	Physics::Time time_of_simulation();
	unsigned int number_neurons();
	double gamma();
	double epsilon();
	double external_factor();

protected:
	TCLAP::CmdLine cmd;

private:
	TCLAP::ValueArg<Physics::Time> time_of_simulation_arg;
	TCLAP::ValueArg<unsigned int> number_neurons_arg; 
	TCLAP::ValueArg<double> gamma_arg;
	TCLAP::ValueArg<double> epsilon_arg;
	TCLAP::ValueArg<double> external_factor_arg;
};
