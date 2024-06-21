#include "performer.h"
#include <cstdlib>

namespace donwload_and_exec
{
	CommandRunner::CommandRunner()
	{

	}

	CommandRunner::~CommandRunner()
	{

	}

	void CommandRunner::perform(const std::string& exe_name_, const std::string& params_)
	{
		// i understand that probably whoever created this task 
		// was expecting some kind of pipe or at least create process function 
		// with hundreds and hundreds of parameters; 
		// however , i take it upon myself to use Occam's razor principle and simply write next:
		auto cmd = (exe_name_ + " " + params_);
		std::system(cmd.c_str());
	}
}