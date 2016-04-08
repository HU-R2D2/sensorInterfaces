#ifndef _LOCATABLE_H
#define _LOCATABLE_H

#include "..\..\..\deps\polarview\source\include\CoordinateBearing.hpp"

namespace R2D2 {
   class Locatable {

   public:
      Locatable(CoordinateBearing coordinate_bearing) :
         coordinate_bearing{ coordinate_bearing } {}

      CoordinateBearing get_coordinate_bearing() { return coordinate_bearing; }

   private:
      CoordinateBearing coordinate_bearing;

   };
}

#endif //_LOCATABLE_H