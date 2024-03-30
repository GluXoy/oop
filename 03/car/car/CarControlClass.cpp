#include "CarClass.h"
#include "CarControlClass.h"
#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
#include <tchar.h>
#include <sstream>

//Instruction StrToInstruction(const std::string& str)
//{
//    return
//        str == "Info" ? Instruction::Info :
//        str == "EngineOn" ? Instruction::EngineOn :
//        str == "EngineOff" ? Instruction::EngineOff :
//        str == "SetGear" ? Instruction::SetGear :
//        str == "SetSpeed" ? Instruction::SetSpeed :
//        throw std::invalid_argument("Invalid instruction!");
//}

//void ExecuteInstruction(Car& car, std::string ins)
//{
//    Instruction instruction = StrToInstruction(ins);
//    if (instruction == Instruction::Info)
//    {
//        car.PrintInfo();
//    }
//    else if (instruction == Instruction::EngineOn)
//    {
//        car.TurnOnEngine();
//    }
//    else if (instruction == Instruction::EngineOff)
//    {
//        car.TurnOffEngine();
//    }
//    else if (instruction == Instruction::SetGear)
//    {
//        std::string gear;
//        do
//        {
//            std::cout << "Enter the gear: ";
//            std::getline(std::cin, gear);
//        } while (!(std::stoi(gear) || gear == "0"));
//        car.SetGear(std::stoi(gear));
//    }
//    else if (instruction == Instruction::SetSpeed)
//    {
//        if (!car.IsTurnedOn())
//        {
//            std::cout << "Engine is turned off!" << std::endl;
//            return;
//        }
//        std::string speed;
//        do
//        {
//            std::cout << "Enter the speed: ";
//            std::getline(std::cin, speed);
//        } while (!(std::stoi(speed) || speed == "0"));
//        car.SetSpeed(std::stoi(speed));
//    }
//}

//m_actionMap.emplace("Info", [this]() {return Info(m_car); });
//m_actionMap.emplace("EngineOn", EngineOn);
//m_actionMap.emplace("EngineOff", EngineOff);
//m_actionMap.emplace("SetGear", SetGear);
//m_actionMap.emplace("SetSpeed", SetSpeed);

CarControl::CarControl(Car& car)
    : m_car(car)
    , m_actionMap({
          { "Info", [this]() { return Info(m_car); } },
          { "EngineOn", [this]() { return EngineOn(m_car); } },
          { "EngineOff", [this]() { return EngineOff(m_car); } },
          { "SetGear", [this]() { return SetGear(m_car); } },
          { "SetSpeed", [this]() { return SetSpeed(m_car); } },
      })
{
}

bool CarControl::Info(Car& car)
{
    std::string EngineInfo = car.IsTurnedOn() ? "Engine: turned on" : "Engine: turned off";
    std::cout << EngineInfo << std::endl;

    std::cout << "Direction: ";
    if (car.GetDirection() == Direction::backward)
    {
        std::cout << "backward" << std::endl;
    }
    else if (car.GetDirection() == Direction::forward)
    {
        std::cout << "forward" << std::endl;
    }
    else
    {
        std::cout << "standing still" << std::endl;
    }

    std::cout << "Gear: " << car.GetGear() << std::endl;

    std::cout << "Speed: " << car.GetSpeed() << std::endl;

    return true;
}

bool CarControl::EngineOn(Car& car)
{
    return car.TurnOnEngine();
}

bool CarControl::EngineOff(Car& car)
{
    return car.TurnOffEngine();
}

bool CarControl::SetGear(Car& car)
{
    std::string gearStr;
    std::cout << "Enter the gear: ";
    std::getline(std::cin, gearStr);

    return car.SetGear(std::stoi(gearStr));
}

bool CarControl::SetSpeed(Car& car)
{
    if (!car.IsTurnedOn())
    {
        std::cout << "Engine is turned off!" << std::endl;
        return false;
    }

    std::cout << "Enter the speed: ";
    std::string speedStr;
    std::getline(std::cin, speedStr);

    int speed = std::stoi(speedStr);

    if (speed < 0)
    {
        std::cout << "Speed must be positive!" << std::endl;
        return false;
    }

    return car.SetSpeed(speed);
}

bool CarControl::HandleCommand()
{
    std::string commandLine;
    std::getline(std::cin, commandLine);
    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        return it->second();
    }

    std::cout << "Unknown command!" << std::endl;
    return false;
}