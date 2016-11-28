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
        TCLAP::ValueArg<Physics::Potential> firing_threshold_arg("F", "firing_threshold", "potential that must be reached to generate a spike", false, 20, "Potential", cmd);
        TCLAP::ValueArg<Physics::Time> refractory_period_arg("r", "refractory", "period during which the neuron is insensitive to arriving spikes", false, 2, "Time", cmd);
        TCLAP::ValueArg<Physics::Potential> resting_potential_arg("p", "resting_potential", "resting potential", false, 0, "Potential", cmd);
        TCLAP::ValueArg<Physics::Potential> reset_potential_arg("P", "reset_potential", "", false, 10, "Time", cmd);
        TCLAP::ValueArg<Physics::Time> transmission_delay_arg("D", "transmission_delay", "duration of the transmission of a spike", false, 1.5, "Time", cmd);
		TCLAP::ValueArg<Physics::Time> tau_arg("T", "tau", "membrane time constant", false, 20, "Time", cmd);
		
        cmd.parse(argc, argv);

        time_of_simulation = time_of_simulation_arg.getValue();
        number_neurons = number_neurons_arg.getValue();
        gamma = gamma_arg.getValue();
        epsilon = epsilon_arg.getValue();
        external_factor = external_factor_arg.getValue();
        time_step = time_step_arg.getValue();
        firing_threshold = firing_threshold_arg.getValue();
        refractory_period = refractory_period_arg.getValue();
        resting_potential = resting_potential_arg.getValue();
        reset_potential = reset_potential_arg.getValue();
        transmission_delay = transmission_delay_arg.getValue();
        tau = tau_arg.getValue();
        
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

Physics::Potential UserArguments::get_firing_threshold()
{
    return firing_threshold;
}
Physics::Time UserArguments::get_refractory_period()
{
    return refractory_period;
}

Physics::Potential UserArguments::get_resting_potential()
{
    return resting_potential;
}

Physics::Potential UserArguments::get_reset_potential()
{
    return reset_potential;
}

Physics::Time UserArguments::get_transmission_delay()
{
    return transmission_delay;
}

Physics::Potential UserArguments::get_tau()
{
    return tau;
}

void UserArguments::print_info()
{
	std::cout << "The simulation time is : " << time_of_simulation << " ms" << std::endl;
	std::cout << "The time step is : " << time_step << " ms" << std::endl;
	std::cout << "The number of neurons is : " << number_neurons << std::endl;
	std::cout << "The proportion of inhibitory over excitatory neurons is : " << gamma << std::endl;
	std::cout << "The connections density is : " << epsilon << std::endl;
	std::cout << "The external factor is : " << external_factor << std::endl;
	std::cout << "The firing threshold is : " << firing_threshold << std::endl;
	std::cout << "The refractory period is : " << refractory_period << std::endl;
	std::cout << "The resting potential is : " << resting_potential << std::endl;
	std::cout << "The reset potential is : " << reset_potential << std::endl;
	std::cout << "The transmission delay is : " << transmission_delay << std::endl;
	std::cout << "The value of tau is : " << tau << std::endl;
}

void UserArguments::print_warning_no_output_neuron_ids()
{
    std::cout << "No output of neurons specified. File will be generated for neuron 0 only [default]." <<  std::endl;
}
