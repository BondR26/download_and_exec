#pragma once

#include <string>


namespace donwload_and_exec
{
	class CommandRunner
	{
	public:
		CommandRunner();

		~CommandRunner();

		void perform(const std::string& exe_name_, const std::string& params_);

	private:


	};
}