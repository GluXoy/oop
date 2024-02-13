#include <iostream>
#include <cmath>
#include <cctype>
#include "stdafx.h"


int CharToInt(char letter)
{
    int digit = 0;
    letter = std::toupper(letter);

    switch (letter) {
    case 'A':
        digit = 10;
        break;
    case 'B':
        digit = 11;
        break;
    case 'C':
        digit = 12;
        break;
    case 'D':
        digit = 13;
        break;
    case 'E':
        digit = 14;
        break;
    case 'F':
        digit = 15;
        break;
    case 'G':
        digit = 16;
        break;
    case 'H':
        digit = 17;
        break;
    case 'I':
        digit = 18;
        break;
    case 'J':
        digit = 19;
        break;
    case 'K':
        digit = 20;
        break;
    case 'L':
        digit = 21;
        break;
    case 'M':
        digit = 22;
        break;
    case 'N':
        digit = 23;
        break;
    case 'O':
        digit = 24;
        break;
    case 'P':
        digit = 25;
        break;
    case 'Q':
        digit = 26;
        break;
    case 'R':
        digit = 27;
        break;
    case 'S':
        digit = 28;
        break;
    case 'T':
        digit = 29;
        break;
    case 'U':
        digit = 30;
        break;
    case 'V':
        digit = 31;
        break;
    case 'W':
        digit = 32;
        break;
    case 'X':
        digit = 33;
        break;
    case 'Y':
        digit = 34;
        break;
    case 'Z':
        digit = 35;
        break;
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


int StringToInt(const std::string& str, int radix, bool& wasError) {
	int numberOfDigits = str.size();
	int result = 0;
	int digit;
	for (int i = 0; i < str.size(); i++)
	{
		if (('0' <= str[i]) && (str[i] <= '9'))
		{
			digit = str[i] - '0';
		} 
		else if (('A' <= str[i]) && (str[i] <= 'Z'))
		{
			digit = CharToInt(str[i]);
		}
		else if (('a' <= str[i]) && (str[i] <= 'z'))
		{
			digit = CharToInt(str[i]);
		}
        else
        {
            wasError = true;
            std::cout << "Invalid number format!" << std::endl;
            return 1;
        }
		result += digit * static_cast<int>(std::pow(radix, --numberOfDigits));
        std::cout << "res[" << i+1 << "] = " << result << std::endl;
	}	
    return result;
}

std::string StringToInt(int num, int radix, bool& wasError)
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
    } while (num >= radix);

    remainder = num % radix;
    if (remainder >= 10)
    {
        result += (IntToChar(remainder));
    }
    else
    {
        result.append(std::to_string(remainder));
    }
    std::reverse(result.begin(), result.end());
    return result;
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	if (argc != 4)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}


	int sourceNotation = std::stoi(argv[1]);      // сделать проверку на диапазон от 2 до 36
	std::cout << sourceNotation << '\n';


	int destinationNotation = std::stoi(argv[2]);   // сделать проверку на диапазон от 2 до 36
	std::cout << destinationNotation << '\n';

	std::string value = argv[3]; // проверять на пустую строку
	std::cout << value << '\n';

    bool wasError = false;

    int tenNotationNumber = StringToInt(value, sourceNotation, wasError);
    if (wasError)
    {
        return 1;
    }
    else
    {
        std::cout << "tenNotationNumber: " << tenNotationNumber << std::endl;
    }

    std::cout << "Result: " << StringToInt(tenNotationNumber, destinationNotation, wasError) << std::endl;
    


	return 0;
}
