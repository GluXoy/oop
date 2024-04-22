#include <iostream>
#include "Calculator.h"
#include "CalculatorPresenter.h"


// нарисовать диаграмуу классов
int main()
{
    Calculator calc;
    CalculatorPresenter calcPres(calc);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "Enter instruction: ";
        try
        {
            if (!calcPres.InputHandler())
            {
                std::cout << "Incorrect expression format!" << std::endl;
            }
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
        std::cout << std::endl;
    }
}
