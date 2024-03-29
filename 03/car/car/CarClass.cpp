#include "CarClass.h"
#include <iostream>
#include <vector>
#include <string>

size_t Car::FindGear(int gear) const
{
    for (size_t i = 0; i < speedRanges.size(); i++)
    {
        if (speedRanges[i].gear == gear)
        {
            return i;
        }
    }
    return std::numeric_limits<size_t>::max();
}

void Car::SetDirection()
{
    if (speed == 0)
    {
        direction = Direction::standing;
    }
    else if (gear == -1)
    {
        direction = Direction::backward;
    }
    else if (speed > 0)
    {
        direction = Direction::forward;
    }
}

Car::Car()
{
    speedRanges =
    {
        {-1, 0, 20},
        {1, 0, 30},
        {2, 20, 50},
        {3, 30, 60},
        {4, 40, 90},
        {5, 50, 150}
    };
}

bool Car::IsTurnedOn() const
{
    return engineIsTurn;
}

Direction Car::GetDirection() const
{
    return direction;
}

int Car::GetSpeed() const
{
    return speed;
}

int Car::GetGear() const
{
    return gear;
}

bool Car::TurnOnEngine()
{
    engineIsTurn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (IsTurnedOn())
    {
        if (GetSpeed() == 0 && GetGear() == 0)
        {
            engineIsTurn = false;
            return true;
        }
        else
        {
            std::cout << "Speed and gear must be on zero!" << std::endl;
            return false;
        }
    }
    return true;
}

bool Car::SetGear(int gear)
{
    if (!IsTurnedOn() && gear != 0)
    {
        std::cout << "Engine is turned off!" << std::endl;
        return false;
    }

    if (!(gear <= GEAR_MAX && gear >= GEAR_MIN))
    {
        std::cout << "The gear isn't in the accept range!" << std::endl;
        return false;
    }

    if (gear == 0)
    {
        this->gear = gear;
        return true;
    }

    if (gear == -1)
    {
        if (GetSpeed() == 0)
        {
            this->gear = gear;
            return true;
        }
        else
        {
            std::cout << "To switch to reverse gear, the speed must be zero!" << std::endl;
            return false;
        }
    }

    if (gear > 0 && GetDirection() == Direction::backward)
    {
        std::cout << "To switch to forward gear, the speed must be zero!" << std::endl;
        return false;
    }

    size_t ind = FindGear(gear);

    if (GetSpeed() >= speedRanges[ind].from && GetSpeed() <= speedRanges[ind].to)
    {
        this->gear = gear;
        return true;
    }
    else
    {
        std::cout << "The current speed isn't in new gear's speed range!" << std::endl;
        return false;
    }
}

bool Car::SetSpeed(int speed)
{
    if (GetGear() == 0)
    {
        if (speed <= GetSpeed())
        {
            this->speed = speed;
            SetDirection();
            return true;
        }
        std::cout << "It is unacceptable to accelerate in neutral gear!" << std::endl;
        return false;
    }

    size_t ind = FindGear(this->gear);

    if (speed >= speedRanges[ind].from && speed <= speedRanges[ind].to)
    {
        this->speed = speed;
        SetDirection();
        return true;
    }
    else
    {
        std::cout << "The new speed isn't in current gear's speed range!" << std::endl;
        return false;
    }
}

void Car::PrintInfo() const
{
    if (IsTurnedOn())
    {
        std::cout << "Engine: turned on" << std::endl;
    }
    else
    {
        std::cout << "Engine: turned off" << std::endl;
    }

    std::cout << "Direction: ";
    if (GetDirection() == Direction::backward)
    {
        std::cout << "backward" << std::endl;
    }
    else if (GetDirection() == Direction::forward)
    {
        std::cout << "forward" << std::endl;
    }
    else
    {
        std::cout << "standing still" << std::endl;
    }

    std::cout << "Gear: " << GetGear() << std::endl;
    std::cout << "Speed: " << GetSpeed() << std::endl;
}

