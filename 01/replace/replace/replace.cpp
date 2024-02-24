#include <iostream>
#include "stdafx.h"
#include "CopyFileAndReplace.h"

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	try
	{
		//функция доолжна не принимать argv
		CopyFileWithReplacement(argv);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}

	return 0;
}
