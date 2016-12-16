#include <iostream>
#include <tclap/CmdLine.h>
#include "UserArguments.hpp"
#include <random>
#include <vector>
#include <stdexcept>
#include <limits>
#include <string>

UserArguments::UserArguments(int argc, char** argv)
{
    parse(argc, argv);
}

void UserArguments::parse(int argc, char** argv)
{
    std::vector <unsigned int> allowed;
    allowed.push_back(0);
    allowed.push_back(1);
    allowed.push_back(2);
    allowed.push_back(3);
    TCLAP::ValuesConstraint<unsigned int> allowedVals( allowed );

    std::random_device rd;
    try
    {
        TCLAP::CmdLine cmd("simulator for Leaky Integrate-and-Fire neurons following a Brunel model");

        TCLAP::SwitchArg verbose_arg("v", "verbose", "output execution parameters", cmd, false);

        const std::string time_of_simulation_msg("total simulation time (unit: ms, validity range: must be positive, default value: " + std::to_string(SIMULATION_TIME) + " ms)");
        TCLAP::ValueArg<Physics::Time> time_of_simulation_arg("t", "time", time_of_simulation_msg, false, SIMULATION_TIME, "Physics::Time", cmd);

        const std::string number_neurons_msg("total number of neurons to consider for the simulation (validity range: must at least have 1, default value: " + std::to_string(NUMBER_OF_NEURONS) + ")");
        TCLAP::ValueArg<unsigned int> number_neurons_arg("n", "neurons", number_neurons_msg, false, NUMBER_OF_NEURONS, "unsigned", cmd);

        const std::string gamma_msg("proportion of inhibitory over excitatory neurons (validity range: must be between 0 and 1, default value: " + std::to_string(GAMMA) + ")");
        TCLAP::ValueArg<double> gamma_arg("g", "gamma", gamma_msg, false, GAMMA, "double", cmd);

        const std::string epsilon_msg("connections density (validity range: must be between 0 and 1, default value: " + std::to_string(EPSILON) + ")");
        TCLAP::ValueArg<double> epsilon_arg("e", "epsilon", epsilon_msg, false, EPSILON, "double", cmd);

        const std::string external_factor_msg("external factor (validity range: must be positive, default value: " + std::to_string(EXTERNAL_FACTOR) + ")");
        TCLAP::ValueArg<double> external_factor_arg("f", "factor", external_factor_msg, false, EXTERNAL_FACTOR, "double", cmd);

        const std::string random_seed_msg("random seed for external events and network connectivity (default value: random)");
        TCLAP::ValueArg<unsigned> random_seed_arg("R", "random_seed", random_seed_msg, false, rd(), "unsigned", cmd);

        const std::string time_step_msg("time step of the simulation (unit: ms, validity range: must be between 0 and the total simulation time, default value: " + std::to_string(TIME_STEP) + " ms)");
        TCLAP::ValueArg<Physics::Time> time_step_arg("d", "dt", time_step_msg, false, TIME_STEP, "Physics::Time", cmd);

        const std::string firing_threshold_msg("potential that must be reached to generate a spike (unit: mV, validity range: must be greater than the resting potential, default value: " + std::to_string(FIRING_THRESHOLD) + " mV)");
        TCLAP::ValueArg<Physics::Potential> firing_threshold_arg("F", "firing_threshold", firing_threshold_msg, false, FIRING_THRESHOLD, "Physics::Potential", cmd);

        const std::string refractory_period_msg("period during which the neuron is insensitive to arriving spikes (unit: ms, validity range: must be between 0 and the total simulation time, default value: " + std::to_string(REFRACTORY_PERIOD) + " ms)");
        TCLAP::ValueArg<Physics::Time> refractory_period_arg("r", "refractory", refractory_period_msg, false, REFRACTORY_PERIOD, "Physics::Time", cmd);

        const std::string resting_potential_msg("resting potential, equilibrium state (unit: mV, validity range: must be lower than the firing threshold, default value: " + std::to_string(RESTING_POTENTIAL) + " mV)");
        TCLAP::ValueArg<Physics::Potential> resting_potential_arg("p", "resting_potential", resting_potential_msg, false, RESTING_POTENTIAL, "Physics::Potential", cmd);

        const std::string reset_potential_msg("potential after the neuron has fired (unit: mV, validity range: must be lower than the firing threshold, default value: "  + std::to_string(RESET_POTENTIAL) + " mV)");
        TCLAP::ValueArg<Physics::Potential> reset_potential_arg("P", "reset_potential", reset_potential_msg, false, RESET_POTENTIAL, "Physics::Time", cmd);

        const std::string transmission_delay_msg("duration of the transmission of a spike (unit: ms, validity range: must be positive, default value: " + std::to_string(TRANSMISSION_DELAY) + " ms)");
        TCLAP::ValueArg<Physics::Time> transmission_delay_arg("D", "transmission_delay", transmission_delay_msg, false, TRANSMISSION_DELAY, "Physics::Time", cmd);

        const std::string tau_msg("membrane time constant (unit: ms, validity range: must be positive, default value: " + std::to_string(TAU) + " ms)");
        TCLAP::ValueArg<Physics::Time> tau_arg("T", "tau", tau_msg, false, TAU, "Physics::Time", cmd);

        TCLAP::ValueArg<unsigned int> simulation_type_arg("m", "mode", "Solution wanted (0 for Analytic_fixed_step, 1 for Explicit, 2 for Implicit, 3 for Variable_step, default value: 0)", false, 0, &allowedVals, cmd);

		TCLAP::SwitchArg add_external_current_arg("E", "external_current", "current arriving from external neurons or not default value: true" , cmd, true);

        const std::string output_neuron_ids_msg("specific neuron id for files opening (id validity range: between 0 and total number of neurons minus one, default value: output only for neuron id equal 0)");
        TCLAP::MultiArg<unsigned int> output_neuron_ids_arg("o", "output", output_neuron_ids_msg, false, "unsigned", cmd, 0);

        const std::string spike_interval_msg("spike counting time interval (unit: ms, validity range: must be between 0 and the total simulation time, default value: " + std::to_string(SPIKE_INTERVAL) + " ms)");
        TCLAP::ValueArg<Physics::Time> spike_interval_arg("s", "spike", spike_interval_msg, false, SPIKE_INTERVAL, "Physics::Time", cmd);
        
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
        simulation_type = simulation_type_arg.getValue();
        spike_interval = spike_interval_arg.getValue();

        check_arguments_validity();

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

unsigned int UserArguments::get_simulation_type()
{
	return simulation_type;
}

Physics::Time UserArguments::get_spike_interval()
{
	return spike_interval;
}

void UserArguments::check_arguments_validity()
{
    Physics::Time time_max (std::numeric_limits<Physics::Time>::max());

    Physics::Potential potential_lowest (std::numeric_limits<Physics::Potential>::lowest());
    Physics::Potential potential_max (std::numeric_limits<Physics::Potential>::max());

    unsigned int unsigned_max (std::numeric_limits<unsigned int>::max());

    double double_max (std::numeric_limits<double>::max());

    // time_of_simulation is in [0, max-Physics::Time]
    if (not(0 <= time_of_simulation && time_of_simulation <= time_max))
        throw std::runtime_error("simulation time not valid; use --help for help");

    // number_neurons is in [1, max-unsigned-int]
    if (not(1 <= number_neurons && number_neurons <= unsigned_max))
        throw std::runtime_error("number of neurons not valid; use --help for help");

    // gamma is in [0, 1]
    if (not(0 <= gamma && gamma <= 1))
        throw std::runtime_error("proportion of inhibitory over excitatory neurons not valid; use --help for help");

    // epsilon is in [0, 1]
    if (not(0 <= epsilon && epsilon <= 1))
        throw std::runtime_error("connections density not valid; use --help for help");

    // external_factor is in [0, max-double]
    if (not(0 <= external_factor && external_factor <= double_max))
        throw std::runtime_error("external factor not valid; use --help for help");

    // random_seed is in [0, max-unsigned-int]
    // unsiged int implies 0 <= random_seed is always true
    if (not(random_seed <= unsigned_max))
        throw std::runtime_error("random seed not valid; use --help for help");

    // time_step is in (0, time_of_simulation]
    if (not(0 < time_step && time_step <= time_of_simulation))
        throw std::runtime_error("time step not valid; use --help for help");

    // firing_threshold is in [resting_potential, max-Physics::Potential]
    if (not(resting_potential <= firing_threshold && firing_threshold <= potential_max))
        throw std::runtime_error("firing threshold not valid; use --help for help");

    // refractory_period is in (0, time_of_simulation]
    if (not(0 < refractory_period && refractory_period <= time_of_simulation))
        throw std::runtime_error("refractory period not valid; use --help for help");

    // resting_potential is in [min-Physics::Potential, firing_threshold]
    if (not(potential_lowest <= resting_potential && resting_potential <= firing_threshold))
        throw std::runtime_error("resting potential not valid; use --help for help");

    // reset_potential is in [min-Physics::Potential, firing_threshold]
    if (not(potential_lowest <= reset_potential && reset_potential <= firing_threshold))
        throw std::runtime_error("reset potential not valid; use --help for help");

    // transmission_delay is in [0, max-Physics::Time]
    if (not(0 <= transmission_delay && transmission_delay <= time_max))
        throw std::runtime_error("transmission delay not valid; use --help for help");

    // tau is in [0, max-Physics::Time]
    if (not(0 <= tau && tau <= time_max))
        throw std::runtime_error("membrane time constant not valid; use --help for help");

    // neuron_id in output_neuron_ids are in [0, number_neurons -1]
    for (unsigned int neuron_id : output_neuron_ids) {
        // unsiged int implies 0 <= neuron_id is always true
        if (not(neuron_id <= number_neurons -1))
            throw std::runtime_error("neuron id for output file not valid; use --help for help");
    }

    // spike_interval is in (0, time_of_simulation]
    if (not(0 < spike_interval && spike_interval <= time_of_simulation))
        throw std::runtime_error("spike interval not valid; use --help for help");
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
    std::cout << "- resting potential: " << resting_potential << " mV" << std::endl;
    std::cout << "- reset potential: " << reset_potential << " mV" << std::endl;
    std::cout << "- firing threshold: " << firing_threshold << " mV" << std::endl;
    std::cout << "- refractory period: " << refractory_period << " ms" << std::endl;
    std::cout << "- transmission delay: " << transmission_delay << " ms" << std::endl;
    std::cout << "- membrane time constant (tau): " << tau << " ms" << std::endl;
    std::cout << "- external current: " << (add_external_current ? "yes" : "no") << std::endl;
    std::cout << "- random seed: " << random_seed << std::endl;
    std::cout << "- spiking rate interval for output: " << spike_interval << " ms" << std::endl;
    //TODO this simulation_type is only correctly printed when calling the 'simulator', not the 'simulator_*' apps
    std::cout << "- simulation type: " << simulation_type << std::endl;
}

void UserArguments::print_warning_no_output_neuron_ids()
{
    std::cout << "No output of neurons specified. File will be generated for neuron 0 only [default]." <<  std::endl;
}
