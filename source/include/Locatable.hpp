#ifndef _LOCATABLE_HPP
#define _LOCATABLE_HPP

#include "../include/CoordinateAttitude.hpp"

namespace r2d2 {
   class Locatable {

   public:
      Locatable(CoordinateAttitude coordinate_attitude) :
         coordinate_attitude{ coordinate_attitude } {}
      CoordinateAttitude get_coordinate_attitude() { return coordinate_attitude; }
   protected:
      CoordinateAttitude coordinate_attitude;
   };
}

#endif //_LOCATABLE_HPP
