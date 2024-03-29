#include <iostream>
#include <vector>
#include <string>
#include "CarClass.h"
#include "CarControlClass.h"


int main()
{
    Car car;
    CarControl carControl(car);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "Enter instruction: ";
        try
        {
            carControl.HandleCommand();
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
        std::cout << std::endl;
    }
}

