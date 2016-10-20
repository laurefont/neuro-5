#pragma once

class CurrentEvent
{

  public:
    CurrentEvent();
    ~CurrentEvent();
    
    double t;
    double current;
    int source_neuron_id;
}
