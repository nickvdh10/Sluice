#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "ITrafficLight.h"
#include "Network.h"

class TrafficLight: public ITrafficLight
{
    public:
        TrafficLight(Network* network, bool lightStatus, int number);
        ~TrafficLight(){}
        bool GetLightStatus();
        std::string SetGreenOn(); //Remove later
        std::string SetGreenOff(); //Remove later
        std::string SetRedOn(); //Remove later
        std::string SetRedOff(); //Remove later
        bool SetGreen();
        bool SetRed();
        std::string CreateTrafficLightMessage(std::string action, std::string colour, int number, bool get);
    private:
		Network* network;
        bool lightStatus;
        int number;
        // Empty copyconst and assignment operator since we don't want copies to be made (?)
		TrafficLight(const TrafficLight&) { /* do nothing */ };
		TrafficLight& operator= (const TrafficLight&) { return *this; };   
};
#endif
