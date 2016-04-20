#ifndef _DISTANCE_SENSOR_HPP
#define _DISTANCE_SENSOR_HPP

#include "Sensor.hpp"
#include "MapPolarView.hpp"

namespace r2d2 {
   class DistanceSensor : public Sensor<MapPolarView> {

   public:
      DistanceSensor(double error) : Sensor{ error } {}
   };
}

#endif //_DISTANCE_SENSOR_HPP
