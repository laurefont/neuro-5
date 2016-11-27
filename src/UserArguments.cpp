#include <iostream>
#include <tclap/CmdLine.h>
#include "UserArguments.hpp"

UserArguments::UserArguments(int argc, char** argv) {
    parse(argc, argv);
}

void UserArguments::parse(int argc, char** argv)
{
    try
    {
        TCLAP::CmdLine cmd("Simulation of neurons network");
        TCLAP::ValueArg<Physics::Time> time_of_simulation_arg("t", "time","total simulation time", false, 1000, "double", cmd);
        TCLAP::ValueArg<unsigned int> number_neurons_arg("n", "neurons", "total number of neurons to consider for the simulation", false, 12500, "int", cmd);
        TCLAP::ValueArg<double> gamma_arg("g", "gamma", "proportion of inhibitory over excitatory neurons", false, 0.25, "double", cmd);
        TCLAP::ValueArg<double> epsilon_arg("e", "epsilon", "connections density", false, 0.1, "double", cmd);
        TCLAP::ValueArg<double> external_factor_arg("f", "factor", "external factor", false, 1, "double", cmd);
        TCLAP::ValueArg<Physics::Time> time_step_arg("d", "dt", "time step of the simulation", false, 2, "Time", cmd);
        TCLAP::MultiArg<unsigned int> file_arg("o", "output", "specific files opening", false, "int", cmd, 0);
		TCLAP::SwitchArg verbose_arg("v", "verbose", "explain what is being done", cmd, false);
        cmd.parse(argc, argv);

        time_of_simulation = time_of_simulation_arg.getValue();
        number_neurons = number_neurons_arg.getValue();
        gamma = gamma_arg.getValue();
        epsilon = epsilon_arg.getValue();
        external_factor = external_factor_arg.getValue();
        time_step = time_step_arg.getValue();
        output_neuron_ids = file_arg.getValue();

        if ( verbose_arg.getValue() )
            print_info();
            
        if ( output_neuron_ids.empty() )
            print_warning_no_output_neuron_ids();
    }
    catch (TCLAP::ArgException& e)
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }
}

UserArguments::~UserArguments(){}

double UserArguments::get_epsilon()
{
    return epsilon;
}

double UserArguments::get_external_factor()
{
    return external_factor;
}

double UserArguments::get_gamma()
{
    return gamma;
}

Physics::Time UserArguments::get_time_of_simulation()
{
    return time_of_simulation;
}

unsigned int UserArguments::get_number_neurons()
{
    return number_neurons;
}

Physics::Time UserArguments::get_time_step()
{
    return time_step;
}

std::vector<unsigned int> UserArguments::get_output_neuron_ids()
{
    return output_neuron_ids;
}

void UserArguments::print_info()
{
	std::cout << "The simulation time is : " << time_of_simulation << " ms" << std::endl;
	std::cout << "The time step is : " << time_step << " ms" << std::endl;
	std::cout << "The number of neurons is : " << number_neurons << std::endl;
	std::cout << "The proportion of inhibitory over excitatory neurons is : " << gamma << std::endl;
	std::cout << "The connections density is : " << epsilon << std::endl;
	std::cout << "The external factor is : " << external_factor << std::endl;
}

void UserArguments::print_warning_no_output_neuron_ids()
{
    std::cout << "No output of neurons specified. File will be generated for neuron 0 only [default]." <<  std::endl;
}
