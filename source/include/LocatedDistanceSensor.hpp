#ifndef _LOCATED_DISTANCE_SENSOR_HPP
#define _LOCATED_DISTANCE_SENSOR_HPP

#include "DistanceSensor.hpp"
#include "Locatable.hpp"
#include "CoordinateAttidude.hpp"

namespace r2d2 {
   class LocatedDistanceSensor : public DistanceSensor, public Locatable {

   public:
      LocatedDistanceSensor(double error, CoordinateAttidude coordinate_attitude) :
         DistanceSensor{ error },
         Locatable{ coordinate_attitude } {}

   };
}

#endif //_LOCATED_DISTANCE_SENSOR_HPP