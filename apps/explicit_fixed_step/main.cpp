#include <UserArguments.hpp>
#include <Simulation.hpp>

int main (int argc, char** argv)
{
    UserArguments user_arguments(argc, argv);

    Simulation simulation(
                          user_arguments.get_number_neurons(),
                          user_arguments.get_time_of_simulation(),
                          user_arguments.get_time_step(),
                          SimulationType::Explicit,
                          user_arguments.get_gamma(),
                          user_arguments.get_epsilon(),
                          user_arguments.get_external_factor(),
                          user_arguments.get_firing_threshold(),
                          user_arguments.get_refractory_period(),
                          user_arguments.get_resting_potential(),
                          user_arguments.get_reset_potential(),
                          user_arguments.get_transmission_delay(),
                          user_arguments.get_tau()
                          );

    simulation.launch_simulation();

    return 0;
}
