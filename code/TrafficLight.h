#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"
#include "Network.h"

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(bool lightStatus);
        ~TrafficLight(){}
        bool GetLightStatus();
        std::string SetGreen();
        std::string SetRed();
        std::string CreateTrafficLightMessage(std::string action, int number, bool get);
    private:
        bool lightStatus;
        
        // Empty copyconst and assignment operator since we don't want copies to be made (?)
		TrafficLight(const TrafficLight&) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };   
};
#endif
