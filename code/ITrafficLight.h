#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

#include <iostream>

class ITrafficLight
{
    public:
        ~ITrafficLight(){}
        bool GetLightStatus();
        std::string SetGreenOn();
        std::string SetGreenOff();
        std::string SetRedOn();
        std::string SetRedOff();
        std::string CreateTrafficLightMessage(std::string action, std::string colour, int number, bool get);

    private:
        int number;
        bool LightStatus;
};
#endif
