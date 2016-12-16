#ifndef EVENT_H
#define EVENT_H

#include "Physics.hpp"

///
/// @brief Neuron state at a definite time
///
/// Event is used to store neurons state in memory.
/// A state is represented by a time point in the simulation and a current intensity.
///
class Event 
{
public:
    /// 
    /// Constructor
    ///
    /// Creates an output to send to a receiving neuron
    ///
    /// @param time time at which the signal reaches the receiving neuron
    /// @param weight_J intensity of the signal
    ///
    Event(Physics::Time const& time, Physics::Amplitude const& weight_J);
    
    ///
    /// @brief Destructor
    ///
    ~Event();

    ///
    /// Compares the times of 2 events to know which one happens first and so which one will be first in the queue
    ///
    /// @param Event reference to another event with which we want to compare the time of occuring
    ///
    bool operator<(Event const&) const;
    
    ///
    /// @brief Get the intensity of the current of the signal
    ///
    /// @return current intensity
    ///
    double get_J() const;
    
    ///
    /// @brief Get the time of the signal
    ///
    /// @return time of occurring signal
    ///
    double get_t() const;
    
private:
    Physics::Time t_; ///< time at which the neuron receives the input
    Physics::Amplitude J_; ///< intensity of the current of the signal
};

#endif // EVENT_H
