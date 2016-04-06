#ifndef _LOCATED_DISTANCE_SENSOR_H
#define _LOCATED_DISTANCE_SENSOR_H

class LocatedDistanceSensor : public DistanceSensor, public Locatable {
	
public:
	LocatedDistanceSensor(double error, CoordinateBearing coordinate_bearing);

};

#endif //_LOCATED_DISTANCE_SENSOR_H