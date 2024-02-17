#include <iostream>
#include <cmath>
#include <cctype>
#include "stdafx.h"
#include "Radix.h"


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    try
    {   
        if (argc != 4)
        {
            throw std::invalid_argument("invalid argument count\n"
                "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>");
        }

        int sourceNotation = std::stoi(argv[1]);
        if ((sourceNotation < 2) || (sourceNotation > 35))
        {
            throw std::out_of_range("invalid source number notation!");
        }

        int destinationNotation = std::stoi(argv[2]);
        if ((destinationNotation < 2) || (destinationNotation > 35))
        {
            throw std::out_of_range("invalid destination number notation!");
        }

        std::string value = argv[3];
        if (value.empty())
        {
            throw std::invalid_argument("the value wasn't initialized!");
        }

        std::cout << "Source notation: " << sourceNotation << '\n';
        std::cout << "Destination notation: " << destinationNotation << '\n';
        std::cout << "Value: " << value << '\n';

        int tempNumber = StringToInt(value, sourceNotation);
        std::cout << "tempNumber: " << tempNumber << '\n';
        std::cout << "Result: " << IntToString(tempNumber, destinationNotation) << '\n';
    }
    catch (std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << '\n';
        return 1;
    }

    // сделать одну функцию ращбора параметров командной строки

	return 0;
}
