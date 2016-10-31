#include <Network.hpp>

#include <cmath>

#include <Physics.hpp>

Network::Network(unsigned int const number_neurons, double const gamma, double const epsilon, double const g)
	: N_(number_neurons),
	  Ne_(std::round(N_ / (1 + gamma))),
	  Ni_(N_ - Ne_),
	  gamma_(gamma),
	  epsilon_(epsilon),
	  g_(g)
{
}

Network::~Network()
{
}

void Network::make_connections()
{
}

void Network::update(Physics::Time dt)
{
}

