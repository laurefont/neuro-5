#ifndef PHYSICS_HPP
#define PHYSICS_HPP


enum class Type : short
{
	Analytic, Explicit, Implicit
};

/**
 * @namespace Physics units and constants
 */
namespace Physics
{
    // Electric potential
    using Potential = double;

    ///
    /// @brief Time unit
    ///
    /// considering units in ms
    ///
    using Time = unsigned int; 
    
    using Resistance = double;
    
    using Amplitude = double;
    
    using Frequency = double;

	///
	/// @brief Dirac delta function
	///
	/// It is zero everywhere except at zero
	///
	int dirac_distribution(Physics::Time argument);
}

#endif // PHYSICS_HPP
