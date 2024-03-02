#include "stdafx.h"
#include "processByteStream.h"

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	try
	{
		ProcessFile(args);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << '\n';
		return 1;
	}

	return 0;
}
