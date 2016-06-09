
#ifndef _DISTANCE_SENSOR_H
#define _DISTANCE_SENSOR_H

#include "Sensor.hpp"
#include "MapPolarView.hpp"

namespace r2d2 {
   class DistanceSensor : public Sensor<r2d2::MapPolarView> {

   public:
      DistanceSensor(double error) : Sensor{ error } {}
   };
}

#endif //_DISTANCE_SENSOR_H