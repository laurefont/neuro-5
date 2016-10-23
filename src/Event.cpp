#include "Event.hpp"
#include <iostream>


Event::Event(double const& time, double const& current) : t_(time), i_(current)
{
}

Event::~Event()
{
}
	
bool Event::operator<(Event const& ev1, Event const& ev2) const
{
	return ev1.t_ < ev2.t_;
}

double Event::get_i() const
{
	return i_;
}
