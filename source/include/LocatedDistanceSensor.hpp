#ifndef _LOCATED_DISTANCE_SENSOR_H
#define _LOCATED_DISTANCE_SENSOR_H

#include "DistanceSensor.hpp"
#include "Locatable.hpp"

namespace R2D2 {
   class LocatedDistanceSensor : public DistanceSensor, public Locatable {

   public:
      LocatedDistanceSensor(double error, int coordinate_attitude) :
         DistanceSensor{ error },
         Locatable{ coordinate_attitude } {}

   };
}

#endif //_LOCATED_DISTANCE_SENSOR_H