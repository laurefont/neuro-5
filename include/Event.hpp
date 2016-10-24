#pragma once

class CurrentEvent
{

  public:
    Event(double const& time, double const& current);
    ~Event();
    bool operator<(Event const&, Event const&) const;
    double get_i() const;
    double get_t() const;
    
    private:
    
    double t_;
    double i_;
    
};

#endif
