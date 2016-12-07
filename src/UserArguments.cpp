#include <iostream>
#include <tclap/CmdLine.h>
#include "UserArguments.hpp"
#include <random>

UserArguments::UserArguments(int argc, char** argv) {
    parse(argc, argv);
}

void UserArguments::parse(int argc, char** argv)
{
	std::random_device rd;
    try
    {
        TCLAP::CmdLine cmd("Simulation of neurons network");
        TCLAP::SwitchArg verbose_arg("v", "verbose", "output execution parameters", cmd, false);
        TCLAP::ValueArg<Physics::Time> time_of_simulation_arg("t", "time","total simulation time", false, SIMULATION_TIME, "Physics::Time", cmd);
        TCLAP::ValueArg<unsigned int> number_neurons_arg("n", "neurons", "total number of neurons to consider for the simulation", false, NUMBER_OF_NEURONS, "int", cmd);
        TCLAP::ValueArg<double> gamma_arg("g", "gamma", "proportion of inhibitory over excitatory neurons", false, GAMMA, "double", cmd);
        TCLAP::ValueArg<double> epsilon_arg("e", "epsilon", "connections density", false, EPSILON, "double", cmd);
        TCLAP::ValueArg<double> external_factor_arg("f", "factor", "external factor", false, EXTERNAL_FACTOR, "double", cmd);
        TCLAP::ValueArg<unsigned> random_seed_arg("R", "random_seed", "random seed for external events and network connectivity (default: random)", false, rd(), "unsigned", cmd);
        TCLAP::ValueArg<Physics::Time> time_step_arg("d", "dt", "time step of the simulation", false, TIME_STEP, "Physics::Time", cmd);
        TCLAP::ValueArg<Physics::Potential> firing_threshold_arg("F", "firing_threshold", "potential that must be reached to generate a spike", false, FIRING_THRESHOLD, "Physics::Potential", cmd);
        TCLAP::ValueArg<Physics::Time> refractory_period_arg("r", "refractory", "period during which the neuron is insensitive to arriving spikes", false, REFRACTORY_PERIOD, "Physics::Time", cmd);
        TCLAP::ValueArg<Physics::Potential> resting_potential_arg("p", "resting_potential", "resting potential", false, RESTING_POTENTIAL, "Physics::Potential", cmd);
        TCLAP::ValueArg<Physics::Potential> reset_potential_arg("P", "reset_potential", "", false, RESET_POTENTIAL, "Physics::Time", cmd);
        TCLAP::ValueArg<Physics::Time> transmission_delay_arg("D", "transmission_delay", "duration of the transmission of a spike", false, TRANSMISSION_DELAY, "Physics::Time", cmd);
        TCLAP::ValueArg<Physics::Time> tau_arg("T", "tau", "membrane time constant", false, TAU, "Physics::Time", cmd);
		TCLAP::SwitchArg add_external_current_arg("E", "external_current", "current arriving from external neurons or not" , cmd, true);
        TCLAP::MultiArg<unsigned int> output_neuron_ids_arg("o", "output", "specific files opening", false, "unsigned	", cmd, 0);
        cmd.parse(argc, argv);

        time_of_simulation = time_of_simulation_arg.getValue();
        number_neurons = number_neurons_arg.getValue();
        gamma = gamma_arg.getValue();
        epsilon = epsilon_arg.getValue();
        external_factor = external_factor_arg.getValue();
        random_seed = random_seed_arg.getValue();
        time_step = time_step_arg.getValue();
        firing_threshold = firing_threshold_arg.getValue();
        refractory_period = refractory_period_arg.getValue();
        resting_potential = resting_potential_arg.getValue();
        reset_potential = reset_potential_arg.getValue();
        transmission_delay = transmission_delay_arg.getValue();
        tau = tau_arg.getValue();
        add_external_current = add_external_current_arg.getValue();
        output_neuron_ids = output_neuron_ids_arg.getValue();

        if ( verbose_arg.getValue() )
            print_info();
            
        if ( output_neuron_ids.empty() )
        {
            print_warning_no_output_neuron_ids();
            output_neuron_ids.push_back(0);
        }
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

unsigned UserArguments::get_random_seed()
{
	return random_seed;
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


std::vector<unsigned int> * UserArguments::get_output_neuron_ids()
{
    return &output_neuron_ids;
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

bool UserArguments::get_add_external_current()
{
	return add_external_current;
}


void UserArguments::print_info()
{
    std::cout << "Execution Parameters:" << std::endl;
    std::cout << "- simulation time: " << time_of_simulation << " ms" << std::endl;
    std::cout << "- time step: " << time_step << " ms" << std::endl;
    std::cout << "- number of neurons: " << number_neurons << std::endl;
    std::cout << "- proportion of inhibitory over excitatory neurons: " << gamma << std::endl;
    std::cout << "- connections density (epsilon): " << epsilon << std::endl;
    std::cout << "- external factor is : " << external_factor << std::endl;
    std::cout << "- firing threshold: " << firing_threshold << std::endl;
    std::cout << "- refractory period: " << refractory_period << std::endl;
    std::cout << "- resting potential: " << resting_potential << std::endl;
    std::cout << "- reset potential: " << reset_potential << std::endl;
    std::cout << "- transmission delay: " << transmission_delay << std::endl;
    std::cout << "- membrane time constant (tau): " << tau << std::endl;
    std::cout << "- external current :" << add_external_current << std::endl;
    std::cout << "- random seed :" << random_seed << std::endl;
}

void UserArguments::print_warning_no_output_neuron_ids()
{
    std::cout << "No output of neurons specified. File will be generated for neuron 0 only [default]." <<  std::endl;
}
