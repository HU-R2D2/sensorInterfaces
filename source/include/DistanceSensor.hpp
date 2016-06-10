#ifndef _DISTANCE_SENSOR_HPP
#define _DISTANCE_SENSOR_HPP

#include "Sensor.hpp"
#include "PolarView.hpp"

#include <memory>

namespace r2d2 {
   class DistanceSensor : public Sensor<std::unique_ptr<PolarView>> {

   public:
      DistanceSensor(double error) : Sensor{ error } {}
   };
}

#endif //_DISTANCE_SENSOR_HPP
