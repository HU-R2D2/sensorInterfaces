#include "../include/UltrasonicSensor.hpp"

namespace r2d2 {
// TODO: Return different sorts of error lengths so we can set the correct DistanceReading::ResultType
// TODO: Perhaps no error lengths but use exceptions instead :-) (Stephan ideas inc.)
    UltrasonicSensor::UltrasonicSensor (
            double error_factor,
            CoordinateAttitude coordinate_attitude,
            int signal,
            int echo
        ):
        LocatedDistanceSensor (error_factor, coordinate_attitude),
        signal { signal },
        echo { echo }

    {}

    DistanceSensor::SensorResult UltrasonicSensor::get_data() {
         // Create a PolarView to hold the data
         std::unique_ptr<PolarView> polarView(new MapPolarView());

         // Length that will hold the distance from the Ultrasonic Sensor
         Length distance;
         // DistanceReading that will hold the distance
         DistanceReading distanceReading(0*Length::METER, DistanceReading::ResultType::CHECKED);
        try {
            // Call get_distance() to get the current distance from the Ultrasonic Sensor
            distance = get_distance();
            // Set the Length of the DistanceReading with ResultType CHECKED as reading was successful
            distanceReading.set_length(distance);
        } catch (OutOfRangeException) {
            // Set the ResultType of the DistanceReading to OUT_OF_RANGE as reading was out of range
            distanceReading.set_result_type(DistanceReading::ResultType::OUT_OF_RANGE);
        } catch (ReadingFailedException) {
            // Set the ResultType of the DistanceReading to DIDNT_CHECK as reading failed
            distanceReading.set_result_type(DistanceReading::ResultType::DIDNT_CHECK);
        }
         // Get the yawAngle which we will use as the angle for the DistanceReading
         Angle yawAngle = coordinate_attitude.get_attitude().get_yaw();

         // Add the DistanceReading to the PolarView at the yawAngle
         polarView->add_distancereading(yawAngle, distanceReading);
         // Create a SensorResult for this reading
         DistanceSensor::SensorResult sensorResult(error_factor, polarView);
         // Return the SensorResult
         return sensorResult;
    }

    Length UltrasonicSensor::get_distance() throw(OutOfRangeException, ReadingFailedException) {
        // If this method gets called within the minimumReadingInterval since previous call, then return an error
        if ((Clock::get_current_time() - lastReadingTimeStamp) < minimumReadingInterval) {
            throw ReadingFailedException();
            //return errorLength;
        }

        // Set the signal pin direction to output
        pin_direction_set_output(signal);

        // Send a pulse on the signal pin
        // Set the signal pin to high
        pin_set(signal, true);
        // Wait the typical amount of time for this input trigger pulse
        wait_us(inputTriggerPulseTime);
        // Set the signal pin to low
        pin_set(signal, false);

        // Set the echo pin direction to input (we do this after the signal pin has been set, and thus used, as some sensors use the same pin for signal and echo)
        pin_direction_set_input(echo);

        // Wait a certain amount of time as reading will start after minimum of 750 us
        wait_us(echoHoldoffTime);

        // Store the time at which we start waiting for the pulse to start
        TimeStamp waitingForPulseStartTimeStamp = Clock::get_current_time();

        // Wait until the echo pin gets set to high (so pin_get() is true)
        while(!pin_get(echo)) {
            // Time difference between now and waiting for pulse to start the signal is larger than the timeout
            if ((Clock::get_current_time() - waitingForPulseStartTimeStamp) > echoTimeout) {
                throw ReadingFailedException();
                //return errorLength;
            }
        }

        // Store the time at which the signal was sent
        TimeStamp signalSentTimeStamp = Clock::get_current_time();

        // Wait until the echo pin gets set to low (so pin_get() is false)
        while(pin_get(echo)) {
            // Time difference between now and sending the signal is larger than the timeout
            if ((Clock::get_current_time() - signalSentTimeStamp) > echoTimeout) {
                throw ReadingFailedException();
                //return errorLength;
            }
        }

        // Store the time at which the echo was received
        TimeStamp echoReceivedTimeStamp = Clock::get_current_time();

        // Store the lastReadingTimeStamp
        lastReadingTimeStamp = echoReceivedTimeStamp;

        // Calculate the difference (Duration is in seconds) between the time at which the signal was sent and the time at which we received an echo
        Duration travelTime = echoReceivedTimeStamp - signalSentTimeStamp;

        // Calculate the approximate speed of sound in dry (0% humidity) air (m/s at temperatures near 0 degrees Celsius)
        Speed speedOfSound  = (speedOfSoundConstant + (temperatureCoefficient * temperature)) * (Length::METER / Duration::SECOND);
        // Calculate the distance to the object (divided by 2 as the sound travels back and forth)
        Length distance = (travelTime * speedOfSound) / 2;

        // As Ultrasonic Sensors have a maximum and a minimum distance, we have to check if the calculated distance is within these values.
        // If this is not the case then return the errorLength
        if ((distance < minimumReadingDistance) || (distance > maximumReadingDistance)) {
            throw OutOfRangeException();
            //return errorLength;
        }

        // If the distance was within the minimum - maximum range, we return the distance
        return distance;
    }

    void UltrasonicSensor::set_temperature(double temperature) {
        this->temperature = temperature;
    }

    double UltrasonicSensor::get_temperature() {
        return this->temperature;
    }

}
