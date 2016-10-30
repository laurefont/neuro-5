#include "Physics.hpp"

#ifndef EVENT_H
#define EVENT_H


class Event {

	public:
	
	/// 
	/// Creates an output to send to a receiving neuron
	///
	/// @param time the time at which the signal reaches the receiving neuron
	/// @param current the intensity of the signal
	///
	Event(Physics::Time const& time, double const& current); 
	

	~Event(); ///<Destructor
	
	
	///
	/// Compares the times of 2 events to know which one happens first and so which one will be first in the queue
	///
	/// @param Event reference to another event with which we want to compare the time of occuring
	///
	bool operator<(Event const&) const;
	
	double get_i() const; ///<returns the intensity of the current of the signal
	
	double get_t() const; ///<returns the time of occuring of the signal
	
	private:
	
	Physics::Time t_; ///< time at which the neuron receives the input
	double i_; ///< intensity of the current of the signal
	

};


#endif
