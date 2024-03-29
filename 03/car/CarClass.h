#pragma once

#include <iostream>
#include <vector>
#include <string>

enum class Direction
{
    forward,
    backward,
    standing
};

struct SpeedRange
{
    int gear;
    int from;
    int to;
};

class Car
{
private:
    const int GEAR_MIN = -1;
    const int GEAR_MAX = 5;

    bool engineIsTurn = false;
    Direction direction = Direction::standing;
    int speed = 0;
    int gear = 0;
    std::vector<SpeedRange> speedRanges;
    size_t FindGear(int gear) const;
    void SetDirection();

public:
    Car();
    bool IsTurnedOn() const;
    Direction GetDirection() const;
    int GetSpeed() const;
    int GetGear() const;
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetGear(int gear);
    bool SetSpeed(int speed);
    void PrintInfo() const;
};