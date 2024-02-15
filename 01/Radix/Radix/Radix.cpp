#include <iostream>
#include <cmath>
#include <cctype>
#include "stdafx.h"

int CharToInt(char letter)
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
        throw std::exception("Invalid number format!");
    }

	return digit;
}

char IntToChar(int num)
{
    if (!(num >= 10 && num <= 35))
    {
        throw std::exception("invalid number format!");
    }

    char letter = 'A' + (num - 10);
    return letter;
}


bool CheckIfNegative(const std::string& str, int& digitsAmount, int& i)
{
    if (str[0] == '-')
    {
        digitsAmount -= 1;
        i = 1;
        return true;
    }
    return false;
}


int StringToInt(const std::string& str, int radix) {
    const int MAX_INT = 2147483647;
    int digitsAmount = str.size();
    int i = 0;
    bool isNegative = CheckIfNegative(str, digitsAmount, i);	
    int result = 0;
	int digit = 0;

	for (i; i < str.size(); i++)
	{        
        digit = CharToInt(str[i]);

        if (digit >= radix)
        {
            throw std::exception("Invalid number format! You should not use digits >= your number notation!");
        }
        
        int multiplicationStep = digit * static_cast<int>(std::pow(radix, --digitsAmount));
        if (MAX_INT - multiplicationStep < result)
        {
            throw std::exception("Overflow!");
        }
        result += multiplicationStep;
        std::cout << "res[" << i+1 << "] = " << result << std::endl;
	}	

    if (isNegative)
    {
        result *= -1;
    }
    return result;
}

std::string IntToString(int num, int radix)
{
    std::string result;
    int remainder = 0;
    bool isNegative = false;
    if (num < 0)
    {
        num *= -1;
        isNegative = true;
    }
    
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
    }
    while (num != 0);

    if (isNegative)
    {
        result.append("-");
    }
    std::reverse(result.begin(), result.end());
    return result;
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    try
    {   
        if (argc != 4)
        {
            throw std::exception("invalid argument count\n"
                "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>");
        }

        int sourceNotation = std::stoi(argv[1]);
        int destinationNotation = std::stoi(argv[2]);
        std::string value = argv[3];

        if ((sourceNotation < 2) || (sourceNotation > 35))
        {
            throw std::exception("invalid source number notation!");
        }

        if ((destinationNotation < 2) || (destinationNotation > 35))
        {
            throw std::exception("invalid destination number notation!");
        }

        if (value.empty())
        {
            throw std::exception("the value wasn't initialized!");
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

	return 0;
}
