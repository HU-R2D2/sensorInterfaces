#ifndef _LOCATABLE_HPP
#define _LOCATABLE_HPP

namespace r2d2 {
   class Locatable {

   public:
      Locatable(int coordinate_attitude) :
         coordinate_attitude{ coordinate_attitude } {}

      int get_coordinate_bearing() { return coordinate_attitude; }

<<<<<<< Updated upstream
   private:
      int coordinate_attitude;

=======
      CoordinateAttitude get_coordinate_attitude() { return coordinate_attitude; }
   protected:
      CoordinateAttitude coordinate_attitude;
>>>>>>> Stashed changes
   };
}

#endif //_LOCATABLE_HPP