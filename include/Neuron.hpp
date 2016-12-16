#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <fstream>
#include <Neuron.hpp>
#include <Physics.hpp>
#include <Event.hpp>
#include <queue>

class Neuron
{
public:
    ///
    /// @brief Constructor
    ///
    /// constructor takes arguments that will be modified during time
    ///
    Neuron(SimulationType const& a_type, 
           bool const& exc,
           bool const& add_external_current = true,
           Physics::Potential firing_threshold = FIRING_THRESHOLD,
           Physics::Time time_of_simulation = SIMULATION_TIME,
           Physics::Time refractory_period = REFRACTORY_PERIOD,
           Physics::Potential resting_potential = RESTING_POTENTIAL,
           Physics::Potential reset_potential = RESET_POTENTIAL,
           Physics::Time transmission_delay = TRANSMISSION_DELAY,
           Physics::Time tau = TAU,
           double const& external_factor = EXTERNAL_FACTOR,
           unsigned random_seed = RANDOM_SEED,
           bool outputCsvFile_ = false,
           int neuron_id_ = 0);

    ///
    /// @brief Destructor
    ///
    ~Neuron();
    
    bool has_reached_threshold() const;  ///< verify if Vm is >= thresold 
    bool update(Physics::Time dt); ///< in a first step, the function updates inputs, then if the thresold is reached, the function update ouputs
    void add_connection(Neuron* neuron); ////< add outgoing synapse
    void step(Physics::Time dt); ///< performs a computation step
    void reset_potential(); ///< function reset the potential, it makes the potentiel return to the reset potential
    Physics::Potential get_Vm() const; ///< returns potential of neuron
    void set_Vm(Physics::Potential vm);
    Physics::Time get_t() const;  ///<returns the time of the neuron
    void output(Physics::Amplitude const& x); ///< fires a spike to all post-synaptic neurons
    void add_event_in(Event const& ev); ///< add spike event to the queue of incoming spikes
    bool is_excitatory(); ///< true if excitatory, false if inhibitory
    int get_synapses_size() const; ///< number of outgoing synapses
    int get_event_in_size() const; ///< number of incoming spikes in queue
    Physics::Time get_transmission_delay() const; ///< returns transmission delay
    Physics::Time get_tau() const; ///< returns tau (time constant)
    int get_neuron_id();

    ///Clears queue of events between t and t+dt and returns the summed
    ///contribution of incoming currents
    Physics::Amplitude RI(Physics::Time const& dt);

    void write_voltage_to_file();

private:
    void step_analytic(Physics::Time const& dt); ///< analytic time-stepping solution
    void step_explicit(Physics::Time const& dt); ///< explicit time-stepping solution
    void step_implicit(Physics::Time const& dt); ///< implicit time-stepping solution

    bool is_not_in_refractory_period(Physics::Time const& dt); ///< true if neuron is in regraction

private:
    int neuron_id_;
    const SimulationType type_;
    const bool outputCsvFile_;

    const double external_factor_;
    Physics::Time t_; ///<time
    std::ofstream * neuron_file; ///< output file for raster plot
    Physics::Amplitude J_; ///< synaptic weight of OUTGOING synapses
    Physics::Potential Vm_; ///< membrane potential
    Physics::Time last_spike_time_; ///< Time of last firing
    std::priority_queue <Event> events_in_; ///<queue of input events 
    std::vector <Neuron*> synapses_; ///<table with the neurons it's sending signals to

    const Physics::Potential firing_threshold_; ///<membrane potential level at which neuron fires
    const Physics::Time refractory_period_; ///<tau_rp (period after an output, during which neuron can't receive inputs and can't fire) 
    const Physics::Potential resting_potential_; ///<resting potential (voltage in equilibrium)
    const Physics::Potential reset_potential_; ///< reset potential after the neuron has fired)
    const Physics::Time transmission_delay_; ///<D (time taken by a signal after it's been produced to reach the receiving neuron)
    const Physics::Time tau_; ///<Time constaint (tau)
};

#endif // NEURON_H
