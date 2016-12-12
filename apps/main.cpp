#include <UserArguments.hpp>
#include <Simulation.hpp>

int main (int argc, char** argv)
{	
	std::cout << "You are in in the simulation of Leaky Integrate-and-Fire Neuron models." << std::endl;
	std::cout <<"Please choose a type of solution" << std::endl;
	std::cout <<"(E for explicit solution, I for implicit solution and A for analytic solution)" << std::endl; 
    char answer1; 
    SimulationType answer2; 
    std::cin >> answer1 ;
    
    if (answer1 == 'E')
    {
		answer2 = SimulationType::ExplicitForwardEuler; 
		
	}
	else if (answer1 == 'I') 
	{
		answer2 = SimulationType::ImplicitBackwardEuler;
		
	}
	else if (answer1 == 'A')
	{
		answer2 = SimulationType::AnalyticVariableStep;
		
	}
	else 
	{	
		std::cout << " Invalide entry. Please choose : E, I or A" <<std::endl; // gerer les mauvaises entrées pour que la simulation ne se lance pas si erreur
	}
	
	
    UserArguments user_arguments(argc, argv);
    
    

    //TODO check if implicit, explicit or analytic and call it 

    Simulation simulation(
                user_arguments.get_number_neurons(),
                user_arguments.get_time_of_simulation(),
                user_arguments.get_time_step(),
                answer2,
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
