#include <iostream>
#include <cctype>
#include "stdafx.h"
#include "Radix.h"

const int RADIX_MIN = 2;
const int RADIX_MAX = 36;


int main(int argc, char* argv[])
{
    try
    {   
        if (argc != 4)
        {
            throw std::invalid_argument("invalid argument count\n"
                "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>");
        }

        int sourceNotation;
        int destinationNotation;
        std::string value;
        //возввращение в виде объекта
        ParseArguments(argv, sourceNotation, destinationNotation, value, RADIX_MIN, RADIX_MAX);
        
        std::cout << "Result: "
            << ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) << '\n';
    }
    catch (std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << '\n';
        return 1;
    }

	return 0;
}
