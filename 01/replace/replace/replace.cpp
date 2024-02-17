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
	// разбить на задачи
	std::ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile.is_open()) 
	{	
		std::cout << "Failed to open" << argv[1] << "for reading" << std::endl;
		return 1;
	}	
	std::cout << "Input file: " << argv[1] << '\n';


	std::ofstream outputFile;
	outputFile.open(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open" << argv[2] << "for writing" << std::endl;
		return 1;
	}
	std::cout << "Output file: " << argv[2] << '\n';

	std::string search = argv[3];
	std::cout << "Search string: " << argv[3] << '\n';

	std::string replace = argv[4];
	std::cout << "Replace string: " << argv[4] << '\n';

	// вынести блок в функцию
	CopyStreamWithReplacement(inputFile, outputFile, search, replace);

	if (!outputFile.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}
