#pragma once

#include <Physics.hpp>
#include <vector>

///
/// @brief Common user arguments parser
///
/// Use the TCLAP library to parse the command line
///
class UserArguments
{
public:
    ///
    /// @brief Constructor
    ///
    /// Parse the user arguments
    ///
    /// @param argc arguments count
    /// @param argv arguments list
    ///
    UserArguments(int argc, char** argv);

    ///
    /// @brief Destructor
    ///
    ~UserArguments();

    ///
    /// @brief Get the simulation time argument
    ///
    /// \f$t_{simulation} \in [0, t_{max}]\f$
    ///
    /// @return \f$t_{simulation}\f$
    ///
    Physics::Time get_time_of_simulation();

    ///
    /// @brief Get the number of neurons argument for the network
    ///
    /// \f$N \in [1, N_{max}]\f$
    ///
    /// @return \f$N\f$
    ///
    unsigned int get_number_neurons();

    ///
    /// @brief Get the proportion of inhibitory over excitatory neurons argument
    ///
    /// \f$\gamma \in [0, 1]\f$
    ///
    /// @return \f$\gamma\f$
    ///
    double get_gamma();

    ///
    /// @brief Get the connections density argument for the network
    ///
    /// \f$\epsilon \in [0, 1]\f$
    ///
    /// @return \f$\epsilon\f$
    ///
    double get_epsilon();

    ///
    /// @brief Get the external factor argument
    ///
    /// \f$\nu_{ext} \in [0, \nu_{max}]\f$
    ///
    /// @return \f$\nu_{ext}\f$
    ///
    double get_external_factor();

    ///
    /// @brief Get random seed argument for the random generators
    ///
    /// The seed is in the unsigned type range
    ///
    /// @return seed
    ///
    unsigned get_random_seed();

    ///
    /// @brief Get the simulation time step argument
    ///
    /// \f$\Delta t_{step} \in (0, t_{simulation}]\f$
    ///
    /// @return \f$\Delta t_{step}\f$
    ///
    Physics::Time get_time_step();

    ///
    /// @brief Get the resting potential argument at the equilibrium state
    ///
    /// At simulation init, the network is in equilibrium state
    ///
    /// \f$V_{rest} \in [V_{min}, \Theta]\f$
    ///
    /// @return \f$V_{rest}\f$
    ///
    Physics::Potential get_resting_potential();

    ///
    /// @brief Get the reset potential argument after a neuron has fired
    ///
    /// \f$V_r \in [V_{min}, \Theta]\f$
    ///
    /// @return \f$V_r\f$
    ///
    Physics::Potential get_reset_potential();

    ///
    /// @brief Get the duration of a spike transmission argument
    ///
    /// \f$D \in [0, t_{max}]\f$
    ///
    /// @return \f$D\f$
    ///
    Physics::Time get_transmission_delay();

    ///
    /// @brief Get the neuron membrane time constant argument
    ///
    /// \f$\tau \in [0, t_{max}]\f$
    ///
    /// @return \f$\tau\f$
    ///
    Physics::Potential get_tau();

    ///
    /// @brief Get the firing threshold argument
    ///
    /// \f$\Theta \in [V_{rest}, V_{max}]\f$
    ///
    /// @return \f$\Theta\f$
    ///
    Physics::Potential get_firing_threshold();

    ///
    /// @brief Get the refractory period argument
    ///
    /// \f$\tau_{rp} \in [0, t_{max}]\f$
    ///
    /// @return \f$\tau_{rp}\f$
    ///
    Physics::Time get_refractory_period();

    ///
    /// @brief argument for the presence of external current arriving
    ///
    /// @return true if there is external current
    ///
    bool get_add_external_current();

    ///
    /// @brief Get the type of simulation calculation argument
    ///
    /// @return 0, 1, 2, or 3
    ///
    unsigned int get_simulation_type();

    ///
    /// @brief Get the spike counting time interval argument
    ///
    /// Used for the results output range
    ///
    /// \f$\Delta t_{count} \in (0, t_{simulation}]\f$
    ///
    /// @return \f$\Delta t_{count}\f$
    ///
    Physics::Time get_spike_interval();

    ///
    /// @brief Get the neurons potential output files argument
    ///
    /// The specified neurons are available
    /// Validity range for neurons id: \f$80, N - 1]\f$
    ///
    /// @return list of neurons id for output
    ///
    std::vector<unsigned int> * get_output_neuron_ids();

private:
    ///
    /// @brief Parse the user arguments
    ///
    /// @param argc arguments count
    /// @param argv arguments list
    ///
    void parse(int argc, char** argv);

    ///
    /// @brief Check for the user arguments validity
    ///
    /// @throw std::runtime_error
    ///
    void check_arguments_validity();

    ///
    /// @brief print the user arguments
    ///
    /// Print in standard output if the verbose flag is enable
    ///
	void print_info();

    ///
    /// @brief print the warnings if no output of neurons specified
    ///
    /// Print warning in standard output
    ///
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

