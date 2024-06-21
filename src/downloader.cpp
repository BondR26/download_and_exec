#include "downloader.h"

#include "smart_curl.h"


namespace download_and_exec
{
	Downloader::Downloader()
	{

	}

	Downloader::~Downloader()
	{

	}

	const std::string& Downloader::download(const std::string& url_, const std::filesystem::path& dest_)
	{
		SmartCurl url(url_);
		absolute_filepath = url.fetchData(dest_.string());

		return absolute_filepath;
	}
}