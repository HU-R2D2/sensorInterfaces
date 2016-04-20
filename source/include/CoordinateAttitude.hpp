#ifndef COORDINATEATTITUDE_H
#define COORDINATEATTITUDE_H

#include "Coordinate.hpp"
#include "Attitude.hpp"
#include "Length.hpp"

namespace r2d2 {

class CoordinateAttitude {
private:
    Coordinate coordinate;
    Attitude attitude;
public:
    CoordinateAttitude() :
        coordinate(0*Length::METER,0*Length::METER,0*Length::METER),
        attitude()
    {}
    CoordinateAttitude(Coordinate coordinate, Attitude attitue) :
        coordinate(coordinate),
        attitude(attitue)
    {}

    Coordinate get_coordinate() { return coordinate; }
    Attitude get_attitude() { return attitude; }

};

}

#endif //COORDINATEATTITUDE_H
