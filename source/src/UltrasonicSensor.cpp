#include "UltrasonicSensor.hpp"

UltrasonicSensor::UltrasonicSensor(
    double error_factor,
    CoordinateBearing coordinate_bearing,
    int signal,
    int echo
    ):
    signal{signal},
    echo{echo}
{}

SensorResult<r2d2::ADT::Length> UltrasonicSensor::get_distance()
{
    // set signal pin high
    // start clock


    r2d2::ADT::Duration
    // wait till echo pin is high

    // stop clock

    r2d2::ADT::Speed speedOfSounds = 1234567.0;
    // TODO: Temperature??
    // Length = (Duration (adt->duration) * (adt->speed) Speed of Sound) / 2

    //r2d2::ADT::Length = 



    // if result is outside of min / max range for sensor
    // return -1
}


