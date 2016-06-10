#ifndef _SENSOR_HPP
#define _SENSOR_HPP

#include <memory>

namespace r2d2 {
   template<class T>
   class Sensor {

   public:
      Sensor(double factor):
         error_factor{ factor }
      {}

      class SensorResult {
          public:
            SensorResult(double error_factor, T& value) :
                error_factor{ error_factor },
                value{ std::move(value) }
            {}

            double get_error_factor() { return error_factor; }
            T get_value() { return std::move(value); }

          private:
              double error_factor;
              T value;
      };

      virtual SensorResult get_data() = 0;

   protected:
      double error_factor;

   };
}

#endif //_SENSOR_HPP
