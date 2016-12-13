#pragma once

#include <Physics.hpp>
#include <vector>

///
/// @brief Common user arguments parser
///
class UserArguments
{
public:
    UserArguments(int argc, char** argv);
    ~UserArguments();

    void parse(int argc, char** argv);
    Physics::Time get_time_of_simulation();
    unsigned int get_number_neurons();
    double get_gamma();
    double get_epsilon();
    double get_external_factor();
    unsigned get_random_seed();
    Physics::Time get_time_step();
    Physics::Potential get_resting_potential();
    Physics::Potential get_reset_potential();
    Physics::Time get_transmission_delay();
    Physics::Potential get_tau();
    Physics::Potential get_firing_threshold();
    Physics::Time get_refractory_period();
    bool get_add_external_current();
    unsigned int get_simulation_type();
    Physics::Time get_spike_interval();

    std::vector<unsigned int> * get_output_neuron_ids();

private:
	void print_info();
    void print_warning_no_output_neuron_ids();

private:
    Physics::Time time_of_simulation;
    Physics::Time time_step;
    unsigned int number_neurons;
    double gamma;
    double epsilon;
    double external_factor;
    unsigned random_seed;
    Physics::Potential firing_threshold;
    Physics::Time refractory_period;
    Physics::Potential resting_potential;
    Physics::Potential reset_potential;
    Physics::Time transmission_delay;
    Physics::Time tau;
    std::vector<unsigned int> output_neuron_ids;
    bool add_external_current;
    unsigned int simulation_type;
    Physics::Time spike_interval;
};

