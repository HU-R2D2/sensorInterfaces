#ifndef _DISTANCE_SENSOR_H
#define _DISTANCE_SENSOR_H

#include "Sensor.hpp"
#include "../../../deps/polarview/source/include/PolarView.hpp"

class DistanceSensor : public Sensor<PolarView> {
	
public:
	DistanceSensor(double error) : Sensor{ error } {}
};

#endif //_DISTANCE_SENSOR_H