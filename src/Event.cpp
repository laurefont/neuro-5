#include <Event.hpp>
#include <iostream>


Event::Event(Physics::Time const& time, Physics::Potential const& weight_J)
    : t_(time), J_(weight_J) {}

Event::~Event() {}
	
bool Event::operator<(Event const& ev1) const
{
    return ev1.t_ < t_;
}

double Event::get_J() const
{
	return J_;
}

double Event::get_t() const
{
	return t_;
}
