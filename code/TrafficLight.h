#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"


class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(Network* network, bool lightStatus, int number);
        ~TrafficLight(){}
        bool GetLightStatus();
        bool SetGreen();
        bool SetRed();
        std::string CreateTrafficLightMessage(std::string action, std::string colour, int number, bool get);
    private:
		Network* network;
        bool lightStatus;
        int number;
        
		TrafficLight(const TrafficLight&) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };   
};
#endif
