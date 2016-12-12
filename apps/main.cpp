#include <UserArguments.hpp>
#include <Simulation.hpp>

int main (int argc, char** argv)

{	
	UserArguments user_arguments(argc, argv);
	
	SimulationType type;
	
	if (user_arguments.get_simulation_type() == 0)
	{
		type = SimulationType::AnalyticFixedStep;
		std:: cout << "Running AnalyticFixedStep simulation..." <<std::endl;
	}
	else if (user_arguments.get_simulation_type() == 1)
	{
		type = SimulationType::ExplicitForwardEuler;
		std:: cout << "Running Explicit simulation..." <<std::endl;
	}
	else if (user_arguments.get_simulation_type() == 2)
	{
		type = SimulationType::ImplicitBackwardEuler;
		std:: cout << "Running Implicit simulation..." <<std::endl;
	}
	else if (user_arguments.get_simulation_type() == 3)
	{
		type = SimulationType::AnalyticVariableStep;
		std:: cout << "Running AnalyticVariableStep simulation..." <<std::endl;
	}
	else 
	{
		type = SimulationType::AnalyticFixedStep;
		std:: cout << "Running AnalyticFixedStep simulation..." <<std::endl;
	}
	

    //TODO check if implicit, explicit or analytic and call it 

    Simulation simulation(
                user_arguments.get_number_neurons(),
                user_arguments.get_time_of_simulation(),
                user_arguments.get_time_step(),
                type,
                user_arguments.get_add_external_current(),
                user_arguments.get_output_neuron_ids(),
                user_arguments.get_firing_threshold(),
                user_arguments.get_refractory_period(),
                user_arguments.get_resting_potential(),
                user_arguments.get_reset_potential(),
                user_arguments.get_transmission_delay(),
                user_arguments.get_tau(),
                user_arguments.get_gamma(),
                user_arguments.get_epsilon(),
                user_arguments.get_external_factor(),
                user_arguments.get_random_seed()
                );

    simulation.launch_simulation();

    return 0;
}
