<<<<<<< HEAD
#include <Event.hpp>
#include <iostream>


Event::Event(double const& time, double const& current) : t_(time), i_(current)
{
}

Event::~Event()
{
}
	
bool Event::operator<(Event const& ev1) const
{
	return t_< ev1.t_;
}

double Event::get_i() const
{
	return i_;
}

double Event::get_t() const
{
	return t_;
}
=======
#include <Event.hpp>
#include <iostream>


Event::Event(Physics::Time const& time, double const& current) : t_(time), i_(current)
{
}

Event::~Event()
{
}
	
bool Event::operator<(Event const& ev1) const
{
	return t_< ev1.t_;
}

double Event::get_i() const
{
	return i_;
}

double Event::get_t() const
{
	return t_;
}

>>>>>>> 218d8ffb0ad64c3bd107378d2a6b541588c93631
