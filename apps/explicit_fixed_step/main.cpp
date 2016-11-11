#include <tclap/CmdLine.h>

int main (int argc, char** argv)
{
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
	
	double time = timeArg.getValue();
	int  neurons = neuronArg.getValue();
	bool time_to_zero = simulation_time_zero_switch.getValue();

	
	std::cout<<"The total number of neurons in the simulation is : "<< neurons << std::endl;
	
	if (time_to_zero)
		{
			std::cout << "The simulation time is now zero" << std::endl;
		}
	
	else
		std::cout << "The simulation time is : " << time << std::endl;


	} catch (TCLAP::ArgException &e)  // catch any exceptions
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
    
    //création d'un neuron "test"
    Neuron neurone(Type::Explicit, true, 1, 1, 2);
    
    neurone.step_explicit(1);
    
    std::cout<<"Step_explicit fonctionne"<<std::endl; //fonctionne bien
    
    neurone.step(1);
    
    std::cout<<"Step fonctionne bien" <<std::endl; //fonctionne bien
    
    Neuron neurone2(Type::Explicit, true, 1, 1, 2);
}
/*
 * Si on ne spécifie rien en lançant le programme, voici la sortie :
 * 
 * The total number of neurons in the simulation is : 12500
   The simulation time is : 1000
 
 * Si on ajoute aux lignes de commande : -n 100000 -t 45 
 * 
 * The total number of neurons in the simulation is : 100000
   The simulation time is : 45
 
 * Si on précise -z :
 * 
 * The total number of neurons in the simulation is : 12500
   The simulation time is now zero
 */

///Remarques : les lettres n, t et z sont appelées "flags". Tous les flags ont un type bien défini. 
///On peut aussi écrire --neurons --time --zero dans le terminal, cela revient au même que de mettre uniquement le "flag"
///Pour vous renseigner sur les divers arguments, leur type et leur description, il existe la commande --help



