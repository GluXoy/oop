#include <iostream>
#include <string>
#include <Windows.h> 
#include "translate.h"


int main(int argc, char* argv[])
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Invalid argument count\n" "Usage: dictionary.exe <inputFile>");
		}
		
		std::string fileName = argv[1];
		WordsTranslater(fileName);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	
	return 0;
}
