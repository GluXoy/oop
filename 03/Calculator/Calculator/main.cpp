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
            calcPres.InputHandler();
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
        std::cout << std::endl;
    }
}
