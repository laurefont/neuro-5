#pragma once

class CurrentEvent
{

  public:
    CurrentEvent();
    ~CurrentEvent();
    
    double time;
    double voltage;
    int source_neuron_id; /*!whether the current comes from an excitatory
							or an ihibitory neuron */
}
