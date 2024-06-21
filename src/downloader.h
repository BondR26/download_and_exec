#pragma once
#include <string>
#include <filesystem>


namespace download_and_exec
{
	class Downloader
	{
	public:
		Downloader();
		~Downloader();

		const std::string& download(const std::string& url_, const std::filesystem::path& dest_);

	private:
		std::string absolute_filepath;
	};
}