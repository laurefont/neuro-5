#pragme once

/**
 * @namespace Physics units and constants
 */
namespace Physics
{
	public:
	
	///ces attributs prennent des valeurs constantes qui ne varient pas 
	///en fonction du temps
	
	double theta_;             ///>firing treshold
	double Vr_;                ///>reset potential
	double Tau_rp_;            ///>refractory period (potential insensitive to stimulation)
	double D_;  		       ///>transmission delay
	double J_;                 ///>postsynaptic potential amplitude
	double Tau_;               ///>membrane time constant
	
	private: 
	
    // Electric potential
    using Potential = double;

    // Time unit
    using Time = double;
    
    
}


