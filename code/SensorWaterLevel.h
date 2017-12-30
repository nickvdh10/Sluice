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
        
        // Empty copyconst and assignment operator since we don't want copies to be made (?)
		SensorWaterLevel(const SensorWaterLevel&) { /* do nothing */ };
		SensorWaterLevel& operator= (const SensorWaterLevel&) { return *this; };   
};
#endif
