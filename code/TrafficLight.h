#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"
#include "Network.h"

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(bool lightStatus, int number);
        ~TrafficLight(){}
        bool GetLightStatus();
        std::string SetGreenOn();
        std::string SetGreenOff();
        std::string SetRedOn();
        std::string SetRedOff();
        std::string CreateTrafficLightMessage(std::string action, std::string colour, int number, bool get);
    private:
        bool lightStatus;
        int number;
        // Empty copyconst and assignment operator since we don't want copies to be made (?)
		TrafficLight(const TrafficLight&) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };   
};
#endif
