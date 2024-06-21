#pragma once
#include <string>
#include <filesystem>

namespace download_and_exec
{
	class CmdParser
	{
	public:
		CmdParser();

		~CmdParser();

		bool parse(int argc, char* cmd_args[]);

		const std::string& getUrl();
		const std::filesystem::path& getDestFolder();
		const std::string& getCommandParams();

	private:
		bool setupDest();
		bool setupUrl();

		std::string _file_url;
		std::filesystem::path _dest;
		std::string _params;
	};
}