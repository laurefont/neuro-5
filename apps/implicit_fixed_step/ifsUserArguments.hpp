#include "UserArguments.hpp"

///
/// @brief Common user arguments parser for implicite fixed step
///
class ifsUserArguments : public UserArguments
{
public:
    ifsUserArguments(int argc, char** argv);
    virtual ~ifsUserArguments();

	Physics::Time time_step();

private:
	TCLAP::ValueArg<Physics::Time> time_step_arg;
};
