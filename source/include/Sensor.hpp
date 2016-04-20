#ifndef _SENSOR_HPP
#define _SENSOR_HPP

namespace r2d2 {
   template<class T>
   class Sensor {

   public:
      Sensor(double factor):
         error_factor{ factor }
      {}

      class SensorResult {
          public:
              SensorResult(double error_factor, T value) :
              error_factor{ error_factor },
              value{ value } {}

             double get_error_factor() { return error_factor; }
             T get_value() { return value; }

          private:
              double error_factor;
              T value;
      };

      virtual SensorResult get_data();

   private:
      double error_factor;

   };
}

#endif //_SENSOR_HPP
