#include <iostream>
#include "Physics.hpp"
#include "Event.hpp"
#include <queue>



class Neuron      
{

	public :
    Neuron(bool const& exc, double const& eps, double const& tau, double const& ext_f, double const& time);
    ~Neuron();
	
	void update(double const& dt); ///>adapt to chrono library
    bool has_reached_threshold() const;
    void input(); ///>modifies current
    double output(double const & dt) const; ///>modifies current
    void reset_potential(); ///>potential goes back to Vr
	void add_event(double const& a_time, double const& a_current);
	double sum_events(double const& dt) const;
	void spike();
    
    private :
	bool excitatory_;          ///>is the neuron excitatory or inhibitory ?
	int Ci_;                   ///>each neuron receives C randomly chosen connections from other neurons in the network
	int Ce_;           	       ///>Ci = connections with inhibitory neurons Ce = connections with excitatory neurons
	double C_proba_;           ///>connection probability
	double V_;                 ///>membrane potential
	double ext_frequency_;     ///>external frequency
	double R_;                 ///>membrane resistance
    
    double t_;
	std::priority_queue <Event> events_;
	std::vector <Neuron*> synapses_;
    
    static const Physics::Potential firing_threshold_;
    static const Physics::Potential rest_potential_; ///>Vr
    static const Physics::Time transmission_delay_; ///>D
    static const Physics::Time refactory_period_; ///>tau_rp
    static const Physics::Resistance membrane_resistance_; ///>R
    static const Physics::Amplitude amplitude_; ///>J
   
              
};

