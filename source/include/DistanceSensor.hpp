#ifndef _DISTANCE_SENSOR_H
#define _DISTANCE_SENSOR_H

#include "Sensor.hpp"
#include "PolarView.hpp"

namespace R2D2 {
   class DistanceSensor : public Sensor<PolarView> {

   public:
      DistanceSensor(double error) : Sensor{ error } {}
   };
}

#endif //_DISTANCE_SENSOR_H