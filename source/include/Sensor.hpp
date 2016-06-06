#ifndef _SENSOR_H
#define _SENSOR_H

namespace R2D2 {
   template<class T>
   class Sensor {

   public:
      Sensor(double factor):
         error_factor{ factor }
      {}
      //virtual T get_data() = 0;

      class SensorResult {
        // SensorResult() error_factor { 0.0f }, value{}
            SensorResult(double error_factor, T value) :
            error_factor{ error_factor },
            value{ value } {}

         double get_error_factor() { return error_factor; }
         T get_value() { return value; }

      private:
         double error_factor;
         T value;
      };

   private:
      double error_factor;

   };
}

#endif //_SENSOR_H