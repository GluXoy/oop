#include "stdafx.h"

int CharToInt(char letter)
{
    letter = std::toupper(letter);

    int digit;

    if (('0' <= letter) && (letter <= '9'))
    {
        digit = letter - '0';
    }
    else if (('A' <= letter) && (letter <= 'Z'))
    {
        digit = ('Z' - 'A') -  ('Z' - letter) + 10;
    }
    else
    {
        throw std::invalid_argument("Invalid number format!");
    }

    return digit;
}

char IntToChar(int num, const int RADIX_MAX)
{
    if (!(num >= 10 && num <= RADIX_MAX))
    {
        throw std::invalid_argument("invalid number format!");
    }

    char letter = 'A' + (num - 10);
    return letter;
}


void ParseArguments(char* argv[], int& sourceNotation, int& destinationNotation, std::string& value,
    const int RADIX_MIN, const int RADIX_MAX)
{
    sourceNotation = std::stoi(argv[1]);
    if ((sourceNotation < RADIX_MIN) || (sourceNotation > RADIX_MAX))
    {
        throw std::out_of_range("invalid source number notation!");
    }

    destinationNotation = std::stoi(argv[2]);
    if ((destinationNotation < RADIX_MIN) || (destinationNotation > RADIX_MAX))
    {
        throw std::out_of_range("invalid destination number notation!");
    }

    value = argv[3];
    if (value.empty())
    {
        throw std::invalid_argument("the value wasn't initialized!");
    }

    std::cout << "Source notation: " << sourceNotation << '\n';
    std::cout << "Destination notation: " << destinationNotation << '\n';
    std::cout << "Value: " << value << "\n\n";
}


bool CheckIfNegative(const std::string& str, size_t& i)
{
    if (str[0] == '-')
    {
        i = 1;
        return true;
    }
    return false;
}


int StringToInt(const std::string& str, int radix) {
    const int MAX_INT = 2147483647;//использовать встроенные константы
    const int MIN_INT = -2147483648;
    size_t digitsAmount = str.size();
    size_t i = 0;
    bool isNegative = CheckIfNegative(str, i);
    int result = 0;
    int digit = 0;

    for (i; i < digitsAmount; i++)
    {
        digit = CharToInt(str[i]);

        if (digit >= radix)
        {
            throw std::invalid_argument("Invalid number format! You should not use digits >= your number notation!");
        }

        if (!isNegative)
        {
            if ((MAX_INT - digit) / radix < result)
            {
                throw std::overflow_error("Overflow!");
            }
            result = result * radix + digit; 
        }
        else
        {
            if ((MIN_INT + digit) / radix > result)
            {
                throw std::overflow_error("Overflow!");
            }
            result = result * radix - digit;
        }
    }
    return result;
}

std::string IntToString(int num, int radix, const int RADIX_MAX)
{
    std::string result;
    int remainder = 0;//объ€вл€ть в цикле
    bool isNegative = false;
    if (num < 0)
    {
        isNegative = true;
    }

    do
    {
        remainder = abs(num % radix);
        if (remainder >= 10)
        {
            result += (IntToChar(remainder, RADIX_MAX));
        }
        else
        {
            // не надо использовать эту функцию(to_string)
            result.append(std::to_string(remainder));
        }
        num /= radix;
    } while (num != 0);

    if (isNegative)
    {
        result.append("-");
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// по значению, а не ссылкой
// не передавать константы
std::string ConvertNotation(int& sourceNotation, int& destinationNotation, std::string& value,
    const int RADIX_MAX)
{
    int tempNumber = StringToInt(value, sourceNotation);
    std::string result = IntToString(tempNumber, destinationNotation, RADIX_MAX);
    return result;
}