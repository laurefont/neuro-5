#ifndef PHYSICS_HPP
#define PHYSICS_HPP

enum class SimulationType : short
{
	Analytic, Explicit, Implicit
};

/**
 * @namespace Physics units and constants
 */
namespace Physics
{
    using Potential  = double; ///< Voltage unit (mV)
    using Time       = double; ///< Time unit (ms)
    using Resistance = double; ///< Resistance unit (ohm)
    using Amplitude  = double; ///< Amplitude unit
}

#endif // PHYSICS_HPP
