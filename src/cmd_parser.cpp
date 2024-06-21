#include "cmd_parser.h"

#include <iostream>
#include <curl/curl.h>

#include "smart_curl.h"

namespace download_and_exec
{
	CmdParser::CmdParser()
	{

	}

	CmdParser::~CmdParser()
	{

	}

	bool CmdParser::setupDest()
	{
		auto res = std::filesystem::exists(_dest);
		if (res)
		{
			std::cout << "Destination location exists\n";
		}
		else
		{
			std::cout << "Destination location doenst exists\n";
			_dest = std::filesystem::current_path();
			std::cout << "Default location is " << _dest.string() << std::endl;
		}

		return res;
	}
	
	bool CmdParser::setupUrl()
	{
		SmartCurl curl(_file_url);
		if (curl.isValidExecutable())
		{
			std::cout << "URL for exe file exists: " << _file_url << std::endl;
			return true;
		}
		else 
		{
			std::cout << "URL does not exist or is executable " << _file_url << std::endl;
			return false;
		}
	}

	bool CmdParser::parse(int argc, char* cmd_args[])
	{
		bool res = false;
		// at least have to have the url
		if (argc > 1)
		{
			// get the url name
			_file_url = cmd_args[1];

			if (setupUrl())
			{
				// check if there is destination folder
				if (argc > 2)
				{
					_dest = cmd_args[2];

					// perfor setting up destination location
					setupDest();

					if (argc > 3)
					{
						_params = cmd_args[3];
					}
				}
				else
				{
					std::cout << "Destination location doenst exists\n";
					_dest = std::filesystem::current_path();
					std::cout << "Default location is " << _dest.string() << std::endl;
				}

				// this is simply the qeustin of whether the url is valid or not
				res = true;
			}
		}
		else
		{
			std::cout << "No url specified\n";
		}

		return res;
	}

	const std::string& CmdParser::getUrl()
	{
		return _file_url;
	}

	const std::filesystem::path& CmdParser::getDestFolder()
	{
		return _dest;
	}

	const std::string& CmdParser::getCommandParams()
	{
		return _params;
	}
}