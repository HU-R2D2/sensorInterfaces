#ifndef _LOCATABLE_H
#define _LOCATABLE_H

namespace R2D2 {
   class Locatable {

   public:
      Locatable(int coordinate_attitude) :
         coordinate_attitude{ coordinate_attitude } {}

      int get_coordinate_bearing() { return coordinate_attitude; }

   private:
      int coordinate_attitude;

   };
}

#endif //_LOCATABLE_H