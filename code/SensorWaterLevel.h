#ifndef SENSORWATERLEVEL_H
#define SENSORWATERLEVEL_H

#include "ISensorWaterLevel.h"

class SensorWaterLevel: public ISensorWaterLevel
{
    public:
        SensorWaterLevel();
        ~SensorWaterLevel(){}
        double GetWaterLevelSluice();
        double GetWaterLevelLow();
        double GetWaterLevelHigh();
    private:
        double waterLevelSluice;
        double waterLevelLow;
        double waterLevelHigh;
};
#endif
