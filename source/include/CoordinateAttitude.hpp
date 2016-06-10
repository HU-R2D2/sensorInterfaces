#ifndef COORDINATEATTITUDE_HPP
#define COORDINATEATTITUDE_HPP

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
    CoordinateAttitude(Coordinate coordinate, Attitude attitude) :
        coordinate(coordinate),
        attitude(attitude)
    {}

    Coordinate getCoordinate() { return coordinate; }
    Attitude getAttitude() { return attitude; }

};

}

#endif //COORDINATEATTITUDE_HPP
