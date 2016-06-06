#ifndef _LOCATABLE_H
#define _LOCATABLE_H

#include "DistanceReading.hpp"

namespace R2D2 {
   class Locatable {

   public:
      Locatable(DistanceReading coordinate_bearing) :
         coordinate_bearing{ coordinate_bearing } {}

      DistanceReading get_coordinate_bearing() { return coordinate_bearing; }

   private:
      DistanceReading coordinate_bearing;

   };
}

#endif //_LOCATABLE_H