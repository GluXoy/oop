#include <iostream>
#include <cmath>
#include <cctype>
#include "stdafx.h"
#include "Radix.h"


int CharToInt(char letter, bool& wasError)
{
    letter = std::toupper(letter);   
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int digit;

    if (('0' <= letter) && (letter <= '9'))
    {
        digit = letter - '0';
    }
    else if (('A' <= letter) && (letter <= 'Z'))
    {
        digit = alphabet.find(letter) + 10;
    }
    else
    {
        wasError = true;
        std::cout << "Invalid number format! Unexpected symbol!" << std::endl;
        return 1;
    }

	return digit;
}

char IntToChar(int num)
{
    char letter;
    if (num >= 10 && num <= 35)
    {
        letter = 'A' + (num - 10);
    }

    return letter;
}


bool CheckIfMinus(const std::string& str, int& digitsAmount, int& i)
{
    if (str[0] == '-')
    {
        digitsAmount -= 1;
        i = 1;
        return true;
    }
    return false;
}


int StringToInt(const std::string& str, int radix, bool& wasError) {
    const int MAX_INT = 2147483647;
    int digitsAmount = str.size();
    int i = 0;
    bool isMinus = CheckIfMinus(str, digitsAmount, i);	
    int result = 0;
	int digit;

	for (i; i < str.size(); i++)
	{        
        digit = CharToInt(str[i], wasError);
        if (wasError)
        {
            return -1;
        }

        if (digit >= radix)
        {
            wasError = true;
            std::cout << "Invalid number format! You should not use digits >= your number notation: " << radix << std::endl;
            return -1;
        }
        
        int multiplicationStep = digit * static_cast<int>(std::pow(radix, --digitsAmount));
        if (MAX_INT - multiplicationStep >= result)
        {
            result += multiplicationStep;
        }
        else
        {
            std::cout << "Overflow!" << std::endl;
            wasError = true;
            return -1;
        }
        std::cout << "res[" << i+1 << "] = " << result << std::endl;
	}	

    if (isMinus)
    {
        result *= -1;
    }
    return result;
}

std::string IntToString(int num, int radix, bool& wasError)
{
    int remainder = num;
    std::string result;
    do
    {
        remainder = num % radix;
        if (remainder >= 10)
        {
            result += (IntToChar(remainder));
        }
        else
        {
            result.append(std::to_string(remainder));
        }
        num /= radix;
    } while (num != 0);

    std::reverse(result.begin(), result.end());
    return result;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
    bool wasError = false;

	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	int sourceNotation = std::stoi(argv[1]);
	if ((sourceNotation < 2) || (sourceNotation > 35))
    {
        std::cout << "Invalid number notation!" << std::endl;
        return 1;
    }
    std::cout << "Source notation: " << sourceNotation << '\n';

	int destinationNotation = std::stoi(argv[2]);
    if ((destinationNotation < 2) || (destinationNotation > 35))
    {
        std::cout << "Invalid number notation!" << std::endl;
        return 1;
    }
    std::cout << "Destination notation: " << destinationNotation << '\n';

	std::string value = argv[3];
    if (value.size() == 0)
    {
        std::cout << "Enter a value!" << '\n';
        return 1;
    }
    std::cout << "Value: " << value << '\n';

    int tempNumber = StringToInt(value, sourceNotation, wasError);
    if (wasError)
    {
        return 1;
    }
    std::cout << "tempNumber: " << tempNumber << std::endl;

    std::cout << "Result: " << IntToString(tempNumber, destinationNotation, wasError) << std::endl;

	return 0;
}
