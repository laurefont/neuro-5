#include "Event.hpp"
#include <iostream>


Event::Event(double const& time, double const& current) : t_(time), i_(current)
{
}

Event::~Event()
{
}
	
bool Event::operator<(Event const& ev1) const
{
	return t_ < ev1.t_;
}

double Event::get_i() const
{
	return i_;
}

double Event::get_t() const
{
	return t_;
}
