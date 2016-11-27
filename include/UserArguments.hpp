#include <Physics.hpp>

///
/// @brief Common user arguments parser
///
class UserArguments
{
public:
    UserArguments(int argc, char** argv);
    ~UserArguments();

    void parse(int argc, char** argv);
    Physics::Time get_time_of_simulation();
    unsigned int get_number_neurons();
    double get_gamma();
    double get_epsilon();
    double get_external_factor();
    Physics::Time get_time_step();
    std::vector<unsigned int> get_output_neuron_ids();

private:
	void print_info();
    void print_warning_no_output_neuron_ids();

private:
    Physics::Time time_of_simulation;
    Physics::Time time_step;
    unsigned int number_neurons;
    double gamma;
    double epsilon;
    double external_factor;
    std::vector<unsigned int> output_neuron_ids;
};
