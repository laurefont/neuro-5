#ifndef PHYSICS_HPP
#define PHYSICS_HPP

/**
 * @namespace Physics units and constants
 */
namespace Physics
{
    // Electric potential
    using Potential = double;

    // Time unit
    using Time = unsigned int;
    
    using Resistance = double;
    
    using Amplitude = double;

	///
	/// @brief Dirac delta function
	///
	/// It is zero everywhere except at zero
	///
	int dirac_distribution(Physics::Time argument);
}

#endif // PHYSICS_HPP
