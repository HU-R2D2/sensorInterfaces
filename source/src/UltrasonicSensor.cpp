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
        // // Timeout after which we will return an error
        // r2d2::Duration minimumReadingInterval = r2d2::Duration(200 * r2d2::Duration::MILLISECOND / 1000); // TODO: Define in UltrasonicSensor.hpp
        
        // if ((r2d2::Clock::get_current_time() - lastReadingTimeStamp) > minimumReadingInterval) {
            // return -1;
        // }        
        
        // Set the signal pin direction to output
        pin_direction_set_output(signal);
        
        // Send a pulse on the signal pin
        // Set the signal pin to high
        pin_set(signal, true);
        // Wait a certain amount of time
        wait_us(5); // TODO: Use this method or some Clock method?
        // Set the signal pin to low
        pin_set(signal, false);

        // Set the echo pin direction to input (we do this after the signal pin has been set, and thus used, as some sensors use the same pin for signal and echo)
        pin_direction_set_input(echo);
        
        // Timeout after which we will return an error
        r2d2::Duration echoTimeout = r2d2::Duration(50 * r2d2::Duration::MILLISECOND); // TODO: Define in UltrasonicSensor.hpp

        // Wait a certain amount of time as reading will start after minimum of 750 us
        wait_us(500); // TODO: Use this method or some Clock method?

        // Store the time at which we start waiting for the pulse to start
        r2d2::TimeStamp waitingForPulseStartTimeStamp = r2d2::Clock::get_current_time();

        // Wait until the echo pin gets set to high (so pin_get() is true)
        while(!pin_get(echo)) {
            // TODO: Maybe sleep?
            // Time difference between now and waiting for pulse to start the signal is larger than the timeout
            if ((r2d2::Clock::get_current_time() - waitingForPulseStartTimeStamp > echoTimeout)) {
                // TODO: return -1; (error)
                break;
            }
        }

        // Store the time at which the signal was sent
        r2d2::TimeStamp signalSentTimeStamp = r2d2::Clock::get_current_time();

        // Wait until the echo pin gets set to low (so pin_get() is false)
        while(pin_get(echo)) {
            // TODO: Maybe sleep?
            // Time difference between now and sending the signal is larger than the timeout
            if ((r2d2::Clock::get_current_time() - signalSentTimeStamp) > echoTimeout) {
                // TODO: return -1; (error)
                break;
            }
        }
       
        // Store the time at which the echo was received
        r2d2::TimeStamp echoReceivedTimeStamp = r2d2::Clock::get_current_time();

        std::cout << std::endl << "Sent: " << signalSentTimeStamp << " Received: " << echoReceivedTimeStamp << " Difference: " << echoReceivedTimeStamp - signalSentTimeStamp << std::endl;
        
        // Calculate the difference between the time at which the signal was sent and the time at which we received an echo
        r2d2::Duration travelTime = echoReceivedTimeStamp - signalSentTimeStamp;
        
        // Calculate the approximate speed of sound in dry (0% humidity) air (m/s at temperatures near 0 degrees Celsius)
        double temperature = 25.0;
        //r2d2::Speed speedOfSound = 331.3 + (0.606 * temperature);
        r2d2::Speed speedOfSound  = (331.3 + (0.606 * temperature)) * (r2d2::Length::METER / r2d2::Duration::SECOND);
        // Calculate the distance to the object (divided by 2 as the sound travels back and forth)
        r2d2::Length distance = ((travelTime * 1000 * 1000) * speedOfSound) / 2; // travelTime times 1000 * 1000 as travelTime is in microseconds
        // Multiply distance by 100 as the distance was in meters and we're interested in centimeters
        distance = distance * 100;
        
        std::cout << "Distance: " << distance << " cm" << std::endl;

        // // As Ultrasonic Sensors have a maximum and a minimum distance, we have to check if the calculated distance is within these values
        // if (2 < distance && distance < 330) {
            // return distance;
        // }
        
        // // If the distance was not within the maximum - minimum range, we return a length of -1        
        // return -1;

        r2d2::Length a = r2d2::Length::METER;
        wait_ms(1000);
        return a;
    }

}
