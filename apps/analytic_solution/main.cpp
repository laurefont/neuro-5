#include <tclap/CmdLine.h>
#include "Simulation.hpp"

int main (int argc, char** argv)
{
	double time = -1;
	int  neurons = -1;
	
	try {
		
	TCLAP::CmdLine cmd("Simulation of neurons network", ' ', "0.9");
	
	
	///le false veut dire que l'utilisateur n'est pas forcément obliger d'entrer une valeur de temps dans les lignes de commande
	///s'il ne saisit pas de valeur, la valeur par défaut (1000 ici) sera prise.
	TCLAP::ValueArg<double> timeArg("t","time","total simulation time",false,1000,"double");
	cmd.add(timeArg);

	///pas obligatoire de saisir une valeur, valeur par défaut = 12500
	TCLAP::ValueArg<int> neuronArg("n","neurons","total number of neurons to consider for the simulation",false,12500,"int"); 
	cmd.add(neuronArg);
	
	///pour mettre le temps de simulation à zéro, valeur par défaut false, si on veut mettre le temps à zéro : ajouter -z ou --zero dans les lignes de commande
	TCLAP::SwitchArg simulation_time_zero_switch("z","zero","Simulation time to zero", cmd, false); 
	
	cmd.parse(argc, argv);
	
	time = timeArg.getValue();
	neurons = neuronArg.getValue();
	bool time_to_zero = simulation_time_zero_switch.getValue();
	
	std::cout<<"The total number of neurons in the simulation is : "<< neurons << std::endl;
	
	if (time_to_zero)
		std::cout << "The simulation time is now zero" << std::endl;
	else
		std::cout << "The simulation time is : " << time << std::endl;
	}
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }

    Simulation sim(time, neurons);
    sim.launch_simulation();
}



