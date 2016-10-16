#ifndef NEURON_H
#define NEURON_H

#include <iostream>



class Neuron      
{
	private :
	
	/// valeurs qui varient au cours du temps
	
	bool excitatory_;          /// is the neuron excitatory or inhibitory ?
	int Ci_;                   /// each neuron receives C randomly chosen connections from other neurons in the network
	int Ce_;           	       /// Ci = connections with inhibitory neurons Ce = connections with excitatory neurons
	double C_proba_;           /// connection probability
	double V_;                 /// membrane potential
	double ext_frequency_;     /// external frequency
	double R_;                 /// membrane resistance
	
	///ces attributs prennent des valeurs constantes qui ne varient pas en fonction du temps que nous initialiserons dans la classe Physics
	
	double theta_;             /// firing treshold
	double Vr_;                /// reset potential
	double Tau_rp_;            /// refractory period (potential insensitive to stimulation)
	double D_;  		       /// transmission delay
	double J_;                 /// postsynaptic potential amplitude
	double Tau_;               /// membrane time constant
	
	public :	
	
	
	Neuron(bool const& exc, int const& Ci, int const& Ce, double const& Cp, double const& PSP, double const& transmission_delay, int const& M_time_constant, int const& firing_treshold, int const& reset_potential, int const& refr_period, double const& ext_f, double const& mem_res);
    
    ~Neuron(); 
    
    double membrane_potential(sf::Time dt);
    /*!
     * @brief calcule le potentiel d'un neurone en fonction des courants entrant aux différents somas et en fonction du temps
     * appelle treshold après chaque pas de temps passé pour vérifier si le seuil est atteint
     */
     
    bool treshold();
    /*!
     * @brief vérifie si le potentiel seuil est atteint
     * si true, appelle spikes
     */
     
    virtual void spikes(); //Inhibitory : transmet potentiel négatif alors que excitatory transmet potentiel positif
    /*!
     * @brief transmet le potentiel d'action aux neurones connectés/voisins
     */
    
    void reset_potential();
    /*!
     * @brief remet le potentiel à Vr après que le neurone ait transmis le potential d'action
     */
     
        
              
};

#endif
