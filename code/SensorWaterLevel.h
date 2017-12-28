#ifndef SENSORWATERLEVEL_H
#define SENSORWATERLEVEL_H

#include "ISensorWaterLevel.h"
#include "Network.h"

class SensorWaterLevel: public ISensorWaterLevel
{
    public:
        SensorWaterLevel();
        ~SensorWaterLevel(){}
        std::string CheckCurrentWaterLevel();
        double GetWaterLevelSluice();
        double GetWaterLevelLow();
        double GetWaterLevelHigh();
    private:
        double waterLevelSluice;
        double waterLevelLow;
        double waterLevelHigh;
};
#endif
