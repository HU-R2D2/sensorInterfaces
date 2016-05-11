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
    // Set the signal pin direction to output
    pin_direction_set_output(signal);
    
    // Set the signal pin to high
    pin_set(signal, true);
    
    // Store the time at which the signal was sent
    auto signalSentTimeStamp = Clock::Timestamp();

    // Set the echo pin direction to input (we do this after the signal pin has been set, and thus used, as some sensors use the same pin for signal and echo)
    pin_direction_set_input(echo);
    
    // Wait until the echo pin gets set to high (so pin_get() is true)
    while(!pin_get(echo)) {
        // TODO: Maybe sleep?
    }
    
    // Store the time at which the echo was received
    auto echoReceivedTimeStamp = Clock::Timestamp();
    
    // Calculate the difference between the time at which the signal was sent and the time at which we received an echo
    auto travelTime = echoReceivedTimeStamp - signalSentTimeStamp;
    
    // Calculate the approximate speed of sound in dry (0% humidity) air (m/s at temperatures near 0 degrees Celsius)
    r2d2::Speed speedOfSound = 331.3 + (0.606 * temperature);
    
    // Calculate the distance to the object (divided by 2 as the sound travels back and forth)
    r2d2::Length distance = (travelTime * speedOfSound) / 2

    // As Ultrasonic Sensors have a maximum and a minimum distance, we have to check if the calculated distance is within these values
    if (2 < distance && distance < 330) {
        return distance;
    }
    
    // If the distance was not within the maximum - minimum range, we return a length of -1
    return -1;
}


