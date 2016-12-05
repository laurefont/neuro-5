#ifndef PHYSICS_HPP
#define PHYSICS_HPP

//see page 9 here for parameters:
//http://arken.nmbu.no//~plesser/publications/Gewa_2012_533_preprint.pdf
#define FIRING_THRESHOLD 20
#define RESTING_POTENTIAL 0
#define RESET_POTENTIAL 10
#define REFRACTORY_PERIOD 2
#define TRANSMISSION_DELAY 1.5
#define TAU 20
#define WEIGHT_J_EXC 0.1
#define WEIGHT_J_INH -0.5
#define GAMMA 0.25 //1 to 4 ratio between Inh and Exc neurons count
#define EPSILON 0.1 //10% connectivity

#define EXTERNAL_FACTOR 0.5
#define NUMBER_OF_NEURONS 10000
#define SIMULATION_TIME 100 //ms
#define TIME_STEP 0.1 //ms

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
