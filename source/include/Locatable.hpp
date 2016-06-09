#ifndef _LOCATABLE_H
#define _LOCATABLE_H

#include "CoordinateAttitude.hpp"

namespace r2d2 {
   class Locatable {

   public:
      Locatable(CoordinateAttitude coordinate_attitude) :
         coordinate_attitude(coordinate_attitude) {}

      CoordinateAttitude get_coordinate_attitude() { return coordinate_attitude; }
   private:
      CoordinateAttitude coordinate_attitude;
   };
}

#endif //_LOCATABLE_H
