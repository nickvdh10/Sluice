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
        void SetGreen();
        void SetRed();
        std::string CreateTrafficLightMessage(std::string action, bool get);
    private:
        bool lightStatus;
        
        // Empty copyconst and assignment operator since we don't want copies to be made (?)
		TrafficLight(const TrafficLight&) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };   
};
#endif
