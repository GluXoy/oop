#include <iostream>
#include "ShapesControl.h"

int main()
{
	ShapesControl shControl;

    while (!std::cin.eof() && !std::cin.fail())
    {   
		try
		{
			shControl.InputHandler();
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
		}
    }

    return 0;
}
