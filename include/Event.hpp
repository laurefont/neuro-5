
#ifndef EVENT_H
#define EVENT_H

class Event {

	public:
	
	Event(double const& time, double const& current);
	~Event();
	bool operator<(Event const&) const;
	double get_i() const;
	double get_t() const;
	
	private:
	
	double t_; ///> time
	double i_; ///> current
	

};


#endif
