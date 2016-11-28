#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <Physics.hpp>
#include <Network.hpp>
#include <UserArguments.hpp>  //why?
#include <vector>

//see page 9 here for parameters:
//http://arken.nmbu.no//~plesser/publications/Gewa_2012_533_preprint.pdf
#define FIRING_THRESHOLD 20
#define RESTING_POTENTIAL 0
#define RESET_POTENTIAL 10
#define REFRACTORY_PERIOD 2
#define TRANSMISSION_DELAY 1.5
#define TAU 20
#define WEIGHT_J_EXC 1
#define WEIGHT_J_INH -0.5
#define GAMMA 0.25 //1 to 4 ratio between Inh and Exc neurons count
#define EPSILON 0.1 //10% connectivity

/**
 * @brief The main class of the simulation
 *
 * Make the simulation of the network and draw the results plot.
 */
class Simulation
{
    public:
        ///
        /// Create a fix step method simulation
        ///
        /// @param number_neurons number of neurons in the network
        /// @param time_of_simulation duration of the simulation
        /// @param time_step time step duration
        /// @param type type of solution
        /// @param gamma proportion of inhibitory neurons over excitatory neurons
        /// @param epsilon connections density
        /// @param external_factor external factor
        ///
        Simulation( unsigned int const number_neurons,
                    Physics::Time const& time_of_simulation,
                    Physics::Time const& time_step,
                    SimulationType const& type,
                    std::vector<unsigned int>* neuron_csv_files = NULL,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = EXTERNAL_FACTOR);


        ///
        /// Create a simulation with an analytic solution
        ///
        /// @param number_neurons number of neurons in the network
        /// @param time_of_simulation duration of the simulation
        /// @param gamma proportion of inhibitory neurons over excitatory neurons
        /// @param epsilon connections density
        /// @param external_factor external factor
		///
        Simulation( unsigned int const number_neurons,
                    Physics::Time const& time_of_simulation,
                    std::vector<unsigned int>* neuron_csv_files = NULL,
                    Physics::Potential firing_threshold = FIRING_THRESHOLD,
                    Physics::Time refractory_period = REFRACTORY_PERIOD,
                    Physics::Potential resting_potential = RESTING_POTENTIAL,\
                    Physics::Potential reset_potential = RESET_POTENTIAL,
                    Physics::Time transmission_delay = TRANSMISSION_DELAY,
                    Physics::Time tau = TAU,
                    double const gamma = GAMMA,
                    double const epsilon = EPSILON,
                    double const& external_factor = EXTERNAL_FACTOR);

        virtual ~Simulation();
        void launch_simulation();
        Network * get_network();
        Physics::Time get_simulation_time();

    private:
        Network network_;
        Physics::Time time_of_simulation_;
        Physics::Time time_step_;
};

#endif // SIMULATION_HPP
