#include "UserArguments.hpp"

///
/// @brief Common user arguments parser for explicit fixed step
///
class efsUserArguments : public UserArguments
{
public:
    efsUserArguments(int argc, char** argv);
    virtual ~efsUserArguments();

	Physics::Time time_step();

private:
	TCLAP::ValueArg<Physics::Time> time_step_arg;
};
