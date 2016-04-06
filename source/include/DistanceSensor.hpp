#ifndef _DISTANCE_SENSOR_H
#define _DISTANCE_SENSOR_H

class DistanceSensor : public Sensor<PolarView> {
	
public:
	DistanceSensor(double error);
	
};

#endif //_DISTANCE_SENSOR_H