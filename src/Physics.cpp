#include <Physics.hpp>

int Physics::dirac_distribution(Physics::Time argument)
{
	if (argument == 0) {
		return 1;
	} else {
		return 0;
	}
}
