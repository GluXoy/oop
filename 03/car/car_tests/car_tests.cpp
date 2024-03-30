#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../car/CarClass.h"
#include "../car/CarControlClass.h"
#include <iostream>
#include <string>
#include <fstream>

TEST_CASE("Checking car's commands")
{
    Car car;
    CarControl carControl(car);

    SECTION("Test Info Command")
    {
        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());
        
        std::stringstream input("Info");
        std::streambuf* oldCin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        carControl.HandleCommand();

        std::cin.rdbuf(oldCin);
        std::cout.rdbuf(oldCout);
        CHECK(output.str() == "Engine: turned off\nDirection: standing still\nGear: 0\nSpeed: 0\n");
    }
}