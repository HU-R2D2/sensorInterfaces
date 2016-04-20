#include "../include/UltrasonicSensor.hpp"
#include <iostream> // TODO: Remove later

namespace r2d2 {

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

    Length UltrasonicSensor::get_distance()
    {
        // Timeout after which we will return an error
        // Duration minimumReadingInterval = Duration(200 * Duration::MILLISECOND / 1000); // TODO: Define in UltrasonicSensor.hpp
        std::chrono::duration<long, std::micro> minimumReadingInterval = std::chrono::microseconds(200);
        
        if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - lastReadingTimeStamp) < minimumReadingInterval) {
            return -1 * Length::CENTIMETER;
        }
        
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
        // r2d2::Duration echoTimeout = r2d2::Duration(50 * r2d2::Duration::MILLISECOND); // TODO: Define in UltrasonicSensor.hpp
        std::chrono::duration<long, std::micro> echoTimeout = std::chrono::milliseconds(50);

        // Wait a certain amount of time as reading will start after minimum of 750 us
        wait_us(500); // TODO: Use this method or some Clock method?

        // Store the time at which we start waiting for the pulse to start
        // r2d2::TimeStamp waitingForPulseStartTimeStamp = r2d2::Clock::get_current_time();
        std::chrono::time_point<std::chrono::high_resolution_clock> waitingForPulseStartTimeStamp = std::chrono::high_resolution_clock::now();

        // Wait until the echo pin gets set to high (so pin_get() is true)
        while(!pin_get(echo)) {
            // TODO: Maybe sleep?
            // Time difference between now and waiting for pulse to start the signal is larger than the timeout
            // if ((Clock::get_current_time() - waitingForPulseStartTimeStamp > echoTimeout)) {
                // // Return -1 centimeter (error)
                // return -1 * Length::CENTIMETER;
            // }
            if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - waitingForPulseStartTimeStamp) > echoTimeout) {
                // Return -1 centimeter (error)
                return -1 * Length::CENTIMETER;
            }
        }

        // Store the time at which the signal was sent
        std::chrono::time_point<std::chrono::high_resolution_clock> signalSentTimeStamp = std::chrono::high_resolution_clock::now();

        // Wait until the echo pin gets set to low (so pin_get() is false)
        while(pin_get(echo)) {
            // TODO: Maybe sleep?
            // Time difference between now and sending the signal is larger than the timeout
            // if ((Clock::get_current_time() - signalSentTimeStamp) > echoTimeout) {
                // // Return -1 centimeter (error)
                // return -1 * Length::CENTIMETER;
            // }
            if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - signalSentTimeStamp) > echoTimeout) {
                // Return -1 centimeter (error)
                return -1 * Length::CENTIMETER;
            }
        }
       
        // Store the time at which the echo was received
        std::chrono::time_point<std::chrono::high_resolution_clock> echoReceivedTimeStamp = std::chrono::high_resolution_clock::now();
        
        // Store the lastReadingTimeStamp
        lastReadingTimeStamp = echoReceivedTimeStamp;

std::chrono::microseconds msSignal = std::chrono::duration_cast<std::chrono::microseconds>(signalSentTimeStamp.time_since_epoch());
std::chrono::microseconds msEcho = std::chrono::duration_cast<std::chrono::microseconds>(echoReceivedTimeStamp.time_since_epoch());
        std::cout << std::endl << "Sent: " << msSignal.count() << " Received: " << msEcho.count() << " Difference: " << msEcho.count() - msSignal.count() << std::endl;
        
        // Calculate the difference (Duration is in seconds) between the time at which the signal was sent and the time at which we received an echo
        std::chrono::duration<long, std::micro> travelTime = std::chrono::duration_cast<std::chrono::microseconds>(echoReceivedTimeStamp - signalSentTimeStamp);
        
        // Calculate the approximate speed of sound in dry (0% humidity) air (m/s at temperatures near 0 degrees Celsius)
        double temperature = 25.0;
        //r2d2::Speed speedOfSound = 331.3 + (0.606 * temperature);
        //Speed speedOfSound  = (331.3 + (0.606 * temperature)) * (Length::METER / Duration::SECOND);
        double speedOfSound = 331.3 + (0.606 * temperature);
        // Calculate the distance to the object (divided by 2 as the sound travels back and forth)
        //Length distance = (travelTime * speedOfSound) / 2 * 1000 * 1000; // travelTime times 1000 * 1000 as travelTime is in microseconds
        double distance = (travelTime.count() * speedOfSound) / 2 / (1000 * 1000);
        // Multiply distance by 100 as the distance was in meters and we're interested in centimeters
        distance = distance * 100; // TODO: Maybe just return Length::METER, as the ADT 'saves' it as meters anyway...
        
        std::cout << "Distance: " << distance << " cm" << std::endl;

        // As Ultrasonic Sensors have a maximum and a minimum distance, we have to check if the calculated distance is within these values
        if (2 < distance && distance < 330) {
            return distance * Length::CENTIMETER;
        }
        
        // If the distance was not within the maximum - minimum range, we return a length of -1        
        return -1 * Length::CENTIMETER;
    }

}
