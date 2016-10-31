#pragma once

#include <iostream>
#include <queue>
#include "CurrentEvent.hpp"

/*!
 * Allows to calculate the membrane potential for each step of time, check if the treshold is reached, if yes, the neuron spikes. 
 */

enum class Neuron_State {AT_REST, FIRING};
enum class Neuron_Type {EXCITATORY, INHIBIROTY};

class Neuron: public Physics 
{
	private :
	
	/// valeurs qui varient au cours du temps
	
	bool excitatory_;          ///>is the neuron excitatory or inhibitory ?
	int connections_inh_;      ///>each neuron receives C randomly chosen connections from other neurons in the network
	int connections_exc_;      ///>Ci = connections with inhibitory neurons Ce = connections with excitatory neurons
	double neuron_voltage_;                 ///>membrane potential
	double R_;                 ///>membrane resistance
	double neuron_id_;
	///Gives a title to the current activity of the neuron
	
	Neuron_State neuron_state;
	
	///< queue of incoming currents sorted by time
	
    std::priority_queue<CurrentEvent> events; 
        
	public :	
	
	Neuron(bool const& exc, int const& connections_inh_, int const& connections_exc_, 
	double const& Cp, double const& PSP, double const& transmission_delay, 
	int const& M_time_constant, int const& firing_treshold, int const& reset_potential, 
	int const& refr_period, double const& ext_f, double const& mem_res);
    
    ~Neuron(); 
    
    void test_neuron_type(Neuron_Type);
    /*!*/
    
    double membrane_potential(sf::Time dt);
    /*!
     * @brief calcule le potentiel d'un neurone en fonction des courants entrant aux différents somas et en fonction du temps
     * appelle treshold après chaque pas de temps passé pour vérifier si le seuil est atteint
     */
     
     virtual void spikes(double current);
     /*!
     * @brief within this function we check if the neuron has reached
     * the threshold if so it sends its current to the neurons connected 
     * to it 
     */
    
    void reset_potential();
    /*!
     * @brief remet le potentiel à Vr après que le neurone ait transmis le potential d'action
     */   
              
};

