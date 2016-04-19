#include "../include/UltrasonicSensor.hpp"
#include <iostream> // TODO: Remove later

namespace R2D2{


UltrasonicSensor::UltrasonicSensor (
        double error_factor,
        int coordinate_attitude,
        int signal,
        int echo
    ):
    LocatedDistanceSensor (error_factor, coordinate_attitude),
    signal { signal },
    echo { echo }
    
{}



r2d2::Length UltrasonicSensor::get_distance()
{
/*pin_direction_set_output(signal);
pin_direction_set_output(echo);
while (1) {
pin_set(signal, true);
pin_set(echo, false);
wait_ms(1000);
pin_set(signal, false);
pin_set(echo, true);
wait_ms(1000);
}*/
    
    // Set the signal pin direction to output
    pin_direction_set_output(signal);
    
    // Send a pulse on the signal pin
    // Set the signal pin to high
    pin_set(signal, true);
    // Wait a certain amount of time
    wait_us(5);
    // Set the signal pin to low
    pin_set(signal, false);

    // Store the time at which the signal was sent
    //auto signalSentTimeStamp = Clock::TimeStamp();

    // Set the echo pin direction to input (we do this after the signal pin has been set, and thus used, as some sensors use the same pin for signal and echo)
    pin_direction_set_input(echo);
    
    Clock::Duration echoTimeout = Clock::Duration(std::chrono::duration<long, std::micro>(5 * 1000 * 10));

    wait_us(500);

    auto waitingForPulseStartTimeStamp = Clock::TimeStamp();

    // Wait until the echo pin gets set to high (so pin_get() is true)
    while(!pin_get(echo)) {
        // TODO: Maybe sleep?
        if ((Clock::TimeStamp() - waitingForPulseStartTimeStamp > echoTimeout)) {
            // TODO: return -1; (error)
            break;
        }
    }

    auto signalSentTimeStamp = Clock::TimeStamp();

    while(pin_get(echo)) {
        if ((Clock::TimeStamp() - signalSentTimeStamp) > echoTimeout) {
            // TODO: return -1; (error)
            break;
        }
    }
   
    // Store the time at which the echo was received
    auto echoReceivedTimeStamp = Clock::TimeStamp();

    std::cout << std::endl << "Sent: " << signalSentTimeStamp << " Received: " << echoReceivedTimeStamp << " Difference: " << echoReceivedTimeStamp - signalSentTimeStamp << std::endl;
    
    // Calculate the difference between the time at which the signal was sent and the time at which we received an echo
    auto travelTime = echoReceivedTimeStamp - signalSentTimeStamp;
    
    // Calculate the approximate speed of sound in dry (0% humidity) air (m/s at temperatures near 0 degrees Celsius)
    double temperature = 25.0;
    //r2d2::Speed speedOfSound = 331.3 + (0.606 * temperature);
    r2d2::Speed speedOfSound  = (331.3 + (0.606 * temperature)) * (r2d2::Length::METER / r2d2::Duration::SECOND);
    // Calculate the distance to the object (divided by 2 as the sound travels back and forth)
    //r2d2::Length distance = (travelTime * speedOfSound) / 2;

    // As Ultrasonic Sensors have a maximum and a minimum distance, we have to check if the calculated distance is within these values
    //if (2 < distance && distance < 330) {
   
        //return distance;
        
    //}
    
    // If the distance was not within the maximum - minimum range, we return a length of -1
   
    
   // return -1

//double distance = (travelTime * (331.3 + (0.606 * temperature))) / 2;
//std::cout << "Distance: " << distance << std::endl;

r2d2::Length a = r2d2::Length::METER;
wait_ms(1000);
        return a;
}

}
