#ifndef _DISTANCE_SENSOR_HPP
#define _DISTANCE_SENSOR_HPP

#include "Sensor.hpp"
#include "PolarView.hpp"

#include <memory>

namespace r2d2 {
<<<<<<< Updated upstream
   class DistanceSensor : public Sensor<r2d2::PolarView> {
=======
   class DistanceSensor : public Sensor<std::unique_ptr<PolarView>> {
>>>>>>> Stashed changes

   public:
      DistanceSensor(double error) : Sensor{ error } {}
   };
}

<<<<<<< Updated upstream
#endif //_DISTANCE_SENSOR_HPP
=======
#endif //_DISTANCE_SENSOR_H
>>>>>>> Stashed changes
