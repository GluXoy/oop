#pragma once
#include <string>
#include "CarClass.h"
#include <functional>
#include <map>

class CarControl
{
private:
    bool Info(Car& car);
    bool EngineOn(Car& car);
    bool EngineOff(Car& car);
    bool SetGear(Car& car);
    bool SetSpeed(Car& car);
    using Handler = std::function<bool()>;
    using ActionMap = std::map<std::string, Handler>;
    ActionMap const m_actionMap;
    Car& m_car;
public:
    CarControl(Car& car);
    CarControl& operator=(const CarControl&) = delete;
    bool HandleCommand();
};
