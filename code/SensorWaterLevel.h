#ifndef SENSORWATERLEVEL_H
#define SENSORWATERLEVEL_H

#include "ISensorWaterLevel.h"


class SensorWaterLevel: public ISensorWaterLevel
{
    public:
        SensorWaterLevel(Network* network);
        ~SensorWaterLevel(){}
        std::string CheckCurrentWaterLevel();

    private:
		Network* network;

		SensorWaterLevel(const SensorWaterLevel&) { /* do nothing */ };
		SensorWaterLevel& operator= (const SensorWaterLevel&) { return *this; };   
};
#endif
