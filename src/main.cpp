#include <iostream>

#include "cmd_parser.h"
#include "performer.h"
#include "downloader.h"


int main(int argc , char * argv[])
{
	download_and_exec::CmdParser parser;
	
	if (parser.parse(argc, argv))
	{
		// at this point there should be
		// url of the file to download
		// the destination location (default or valid)
		// the additional params

		download_and_exec::Downloader downloader;
		auto app_name = downloader.download(parser.getUrl(), parser.getDestFolder());

		donwload_and_exec::CommandRunner excutioner;
		excutioner.perform(app_name, parser.getCommandParams());
	}

	return EXIT_SUCCESS;
}