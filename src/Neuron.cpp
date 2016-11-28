#include "Neuron.hpp"
#include <cmath>
#include <string>
#include <assert.h>
#include <chrono>
#include <random>
#include <Neuron.hpp>

unsigned int Neuron::neuron_id_ = 0;
/*Physics::Potential const Neuron::firing_threshold_= FIRING_THRESHOLD;
Physics::Time const Neuron::refractory_period_ = REFRACTORY_PERIOD;
Physics::Potential const Neuron::resting_potential_= RESTING_POTENTIAL;
Physics::Potential const Neuron::reset_potential_= RESET_POTENTIAL;
Physics::Time const Neuron::transmission_delay_= TRANSMISSION_DELAY;
Physics::Time const Neuron::tau_ = TAU;*/

using namespace std;

Neuron::Neuron(SimulationType const& a_type, bool const& exc, Physics::Potential firing_threshold,
			   Physics::Time refractory_period, Physics::Potential resting_potential ,Physics::Potential reset_potential, 
			   Physics::Time transmission_delay, Physics::Time tau, double const& external_factor, bool outputCsvFile, double initial_Vm)
                : type_(a_type), external_factor_(external_factor), t_(0), neuron_file(NULL),
                  firing_threshold_(firing_threshold), refractory_period_(refractory_period), resting_potential_(resting_potential),
                  reset_potential_(reset_potential), transmission_delay_(transmission_delay), tau_(tau)
                  
{
    Vm_ = initial_Vm;
    last_spike_time_ = -Neuron::refractory_period_;
    //no spike is added between last_spike_time_ and last_spike_time_+refractory_period
    //see add_event_in() function (discards spikes during refraction)

    J_ = exc ? WEIGHT_J_EXC : WEIGHT_J_INH; //if (exc) J_=WEIGHT_EXC; else J_=WEIGHT_INH;

    if (outputCsvFile)
    {
        string fileName =  "neuron_" + to_string(neuron_id_) + ".csv";
        neuron_file = new ofstream(fileName);
        if (neuron_file && neuron_file->fail()) {
            throw string("Error: The file doesn't exist !");
        } else {
            *neuron_file << "t,vm" << endl;
        }
    }

    ++neuron_id_;
}


Neuron::~Neuron()
{  
    if (neuron_file)
    {
      neuron_file->close();
      delete neuron_file;
    }
}

void Neuron::output(double const& x)
{
    Event ev(t_+transmission_delay_, x);

    for (auto& s : synapses_)
        s->add_event_in(ev);
}


bool Neuron::has_reached_threshold() const
{
    return Vm_ >= firing_threshold_;
}


void Neuron::add_event_in(Event const& ev)
{
    //only adds spikes that are delivered after refraction
    if (ev.get_t() >= last_spike_time_ + refractory_period_)
        events_in_.push(ev);
}


// remet le potentiel de membrane au potentiel au repos, cette méthode sera appelée
// dans update si le threshold est dépassé
void Neuron::reset_potential()
{
    Vm_ = reset_potential_;
}


double Neuron::external_spike_generator(Physics::Time const& dt)
{
	/// Construct a random generator engine from a time-based seed
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	/// Use a Poisson distribution with a rate 
	//std::poisson_distribution<double> distribution(external_factor_*dt);
	//return distribution(generator);
	return 0;		
}

void Neuron::update(Physics::Time dt)
{
    //real step size is the minimum of max step or until arrival of next event
    if (type_ == SimulationType::Analytic)
        if (!events_in_.empty())
            dt = std::min(dt, events_in_.top().get_t() - t_);

    step(dt); //updates Voltage based on step size

    if (has_reached_threshold())
    {
        output(J_);
        if (neuron_file)
            *neuron_file << t_ << "," << Vm_ << endl;
        last_spike_time_ = t_;
        reset_potential();

        if (type_ == SimulationType::Analytic)
        {
            if (neuron_file)
                *neuron_file << t_ << "," << Vm_ << endl;
            t_ += refractory_period_;
        }
    }
   
    if (neuron_file)
        *neuron_file << t_ << "," << Vm_ << endl;
}

void Neuron::add_connection(Neuron* neuron)
{
    assert(neuron!=NULL);
	synapses_.push_back(neuron);
}

void Neuron::step(Physics::Time dt) // faire en sorte que dans commandline on puisse entrer que 0,1,2
{
	switch(type_)
	{
        case SimulationType::Analytic :
             step_analytic(dt);
		     break;

        case SimulationType::Explicit :
		     step_explicit(dt);
		     break;

        case SimulationType::Implicit :
		     step_implicit(dt);
		     break;
	}
    t_+=dt;
}


void Neuron::step_analytic(Physics::Time const& dt)
{
	for (int i=1; i<4; i++)
    {
		double temp_Vm = Vm_ * exp((-dt/4*i)/tau_);
        if (neuron_file)
          *neuron_file << this->t_ + dt/4*i  << "," << temp_Vm << endl;
    }

    Vm_ *= exp(-dt/tau_);  //calculate decay from previous timestep
    Vm_ += RI(dt)*dt/tau_; //sum voltage from network contributions at next timestep
                   //eq 1.8 in http://neuronaldynamics.epfl.ch/online/Ch1.S3.html
}


void Neuron::step_explicit(Physics::Time const& dt)// Use of V(t-1)=Vm_ to calculate the new Vm_
{
    Vm_ += ((-Vm_ + RI(dt)) * dt) / tau_;
}


void Neuron::step_implicit(Physics::Time const& dt)
{
    Vm_ = ((dt * RI(dt) ) + (tau_ * Vm_)) / ( dt + tau_);
}

Physics::Amplitude Neuron::RI(Physics::Time const& dt)
{
    Physics::Amplitude sum_incoming_J = 0;
    //sum all contributions of spikes arriving between t and t+dt
    //(in analytic solytion the t+dt will only have 1 event)
    //(+0.000000001 is to fix rounding errors in time)
    while(!events_in_.empty() && events_in_.top().get_t() <= t_ + dt + 0.000000001)
    {
        assert(events_in_.top().get_t()>=t_);
        sum_incoming_J += events_in_.top().get_J();
        events_in_.pop();
	}
    return tau_ * sum_incoming_J;
}


Physics::Time Neuron::get_t() const
{
	return t_;
}

double Neuron::get_Vm() const
{
	return Vm_;
}

void Neuron::set_Vm(Physics::Potential vm)
{
    Vm_=vm;
}

int Neuron::get_synapses_size() const
{
	return synapses_.size();
}

int Neuron::get_event_in_size() const
{
	return events_in_.size();
}

Physics::Time Neuron::get_transmission_delay() const
{
    return transmission_delay_;
}

Physics::Time Neuron::get_tau() const
{
    return tau_;
}

bool Neuron::is_excitatory()
{
    assert(J_!=0);
    return J_ > 0;
}
