#include "Neuron.hpp"
#include <cmath>
#include <string>
#include <iomanip>
#include <assert.h>
#include <chrono>
#include <random>
#include <Neuron.hpp>





using namespace std;

Neuron::Neuron(SimulationType const& a_type, bool const& exc,
               bool const& add_external_current, Physics::Potential firing_threshold, Physics::Time time_of_simulation,
			   Physics::Time refractory_period, Physics::Potential resting_potential, Physics::Potential reset_potential, 
               Physics::Time transmission_delay, Physics::Time tau, double const& external_factor, unsigned random_seed,
               bool outputCsvFile, int neuron_id)
                : neuron_id_(neuron_id),
				  type_(a_type), 
				  outputCsvFile_(outputCsvFile),
				  external_factor_(external_factor), 
				  t_(0), 
				  neuron_file(NULL),
                  Vm_(resting_potential),
                  firing_threshold_(firing_threshold), 
                  refractory_period_(refractory_period), 
                  resting_potential_(resting_potential),
                  reset_potential_(reset_potential), 
                  transmission_delay_(transmission_delay),
                  tau_(tau)
                 

                  
                  
{
    //no spike is added between last_spike_time_ and last_spike_time_+refractory_period
    //see add_event_in() function (discards spikes during refraction)
    last_spike_time_ = -Neuron::refractory_period_;

     //if (exc) J_=WEIGHT_EXC; else J_=WEIGHT_INH;
    J_ = exc ? WEIGHT_J_EXC : WEIGHT_J_INH;

    if (add_external_current)
    {
      //insert all the external spikes in the queue
      // std::random_device rd; plus besoin
      //std::cout << random_seed + neuron_id_ << endl;
	  std::mt19937 gen(random_seed + neuron_id_);
	
      //calculates lambda = parameter of the exponential process for the external spikes generator (Analytical)
      double lambda = (external_factor_ * firing_threshold_) / (WEIGHT_J_EXC * tau_);
      assert(lambda>0);
	
      std::exponential_distribution<> d(lambda);
      for ( Physics::Time last_external_spike_sent =  d(gen);
            last_external_spike_sent < time_of_simulation;
            last_external_spike_sent += d(gen))
      {
         add_event_in(Event(last_external_spike_sent, WEIGHT_J_EXC));
      }
      //printf("Neuron %d, total external events for whole simulation: %d\n", get_neuron_id(), events_in_.size());
    }
	
    if (outputCsvFile)
    {
        string fileName =  "neuron_" + to_string(neuron_id_) + ".csv";
        neuron_file = new ofstream(fileName);
        if (neuron_file && neuron_file->fail()) {
            throw string("Error: The file doesn't exist !");
        } else {
            *neuron_file << "t,vm" << endl;
            write_voltage_to_file();
        }
    }
}


Neuron::~Neuron()
{  
    if (neuron_file)
    {
      neuron_file->close();
      delete neuron_file;
    }
}

int Neuron::get_neuron_id()
{
    return neuron_id_;
}

void Neuron::output(Physics::Amplitude const& x)
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
    //if this fails: either this neuron jumped too much in time, or event was delivered wrongly
    assert(ev.get_t() >= last_spike_time_);

    //only adds spikes that are delivered after refraction
    if (ev.get_t() >= last_spike_time_ + refractory_period_)
        events_in_.push(ev);
}


void Neuron::reset_potential()
{
    Vm_ = reset_potential_;
}


bool Neuron::update(Physics::Time dt)
{
	//TODO
    //make sure I didn't miss any event (leave the {...} around the assert, it's a macro)
    //if (!events_in_.empty())
        //{assert(events_in_.top().get_t() + 0.00001 >= t_); }

    //remove all future events during my refraction period (if applicable)
    while(!events_in_.empty() && events_in_.top().get_t() < last_spike_time_ + refractory_period_)
        events_in_.pop();

    //real step size is the minimum of max step or until arrival of next event (outside refrection)
    if (type_ == SimulationType::AnalyticVariableStep)
        if (!events_in_.empty())
            dt = std::min(dt, events_in_.top().get_t() - t_);

    assert(dt>=0);
    step(dt); //updates Voltage based on step size
    write_voltage_to_file();

    if (has_reached_threshold())
    {
        output(J_);
        
        last_spike_time_ = t_;
        reset_potential();
        write_voltage_to_file(); //draw vertical line for drop of voltage

        //fixed absolute refractory period for variable step only
        if (type_ == SimulationType::AnalyticVariableStep)
        {
            t_ += refractory_period_;
            write_voltage_to_file(); //horizontal line for fixed refractory period
        }
        return true;
    }
    return false;
}

void Neuron::write_voltage_to_file()
{
    if (neuron_file)
        *neuron_file << t_ << "," << std::fixed << std::setprecision(3) << Vm_ << endl;
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
        case SimulationType::AnalyticVariableStep:
        case SimulationType::AnalyticFixedStep:
             step_analytic(dt);
		     break;

        case SimulationType::ExplicitForwardEuler :
		     step_explicit(dt);
		     break;

        case SimulationType::ImplicitBackwardEuler :
		     step_implicit(dt);
		     break;
	}
    t_+=dt;
}

bool Neuron::is_not_in_refractory_period(Physics::Time const& dt)
{
    return t_ + dt >= last_spike_time_ + refractory_period_;
}

void Neuron::step_analytic(Physics::Time const& dt)
{
    //This condition is only useful for analytic solution with fixed step
    if( is_not_in_refractory_period(dt) )
    {
      //Commented so that we  output less points
      /*
      //Plot intermediate points for decay
      if (type_ == SimulationType::Analytic)
      {
        if (neuron_file)
          for (int i=1; i<4; i++)
          {
            double temp_Vm = Vm_ * exp((-dt/4*i)/tau_);
            *neuron_file << this->t_ + dt/4*i  << "," <<  std::fixed << std::setprecision(3) << temp_Vm << endl;
          }
      }
      */

      Vm_ *= exp(-dt/tau_);  //calculate decay from previous timestep
      //Vm_ += RI(dt)/tau_*(1-exp(-dt/tau_)); //slides from professor
      Vm_ += RI(dt)/tau_; //vertical jump in voltage (same as before but without exp growth)
    }
}


void Neuron::step_explicit(Physics::Time const& dt)
{ 
    if( is_not_in_refractory_period(dt) )
    {
       //we divide RI(dt) by dt because when we integrate the dirac-function in
       //RI we get the delta function, dividing it by dt gives us the dirac
       //Vm_ += (-Vm_ + RI(dt))/tau_ * dt; //OLD
       Vm_ += (-Vm_ + RI(dt)/dt)/tau_ * dt;
    }
}


void Neuron::step_implicit(Physics::Time const& dt)
{
    if( is_not_in_refractory_period(dt) )
	{
        //Vm_ = ((dt * RI(dt) ) + (tau_ * Vm_)) / ( dt + tau_); //OLD
        Vm_ = (RI(dt) + (tau_ * Vm_)) / ( dt + tau_);
    }
}

Physics::Amplitude Neuron::RI(Physics::Time const& dt)
{
    Physics::Amplitude sum_incoming_J = 0;
    //sum all contributions of spikes arriving between t and t+dt
    //(in analytic solytion the t+dt will only have 1 event)
    //(+0.000000001 is to fix rounding errors in time)
    while(!events_in_.empty() && events_in_.top().get_t() <= t_ + dt + 0.0001)
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

	
