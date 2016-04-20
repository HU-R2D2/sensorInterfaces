#include "../include/UltrasonicSensor.hpp"

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

    Sensor<MapPolarView>::SensorResult UltrasonicSensor::get_data() {
         MapPolarView mapPolarView = MapPolarView();
         Sensor<MapPolarView>::SensorResult sensorResult(0.0, mapPolarView);
         return sensorResult;
    }

    Length UltrasonicSensor::get_distance()
    {
        // If this method gets called within the minimumReadingInterval since previous call, then return an error
        if ((Clock::get_current_time() - lastReadingTimeStamp) < minimumReadingInterval) {
            return errorLength;
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
                return errorLength;
            }
        }

        // Store the time at which the signal was sent
        TimeStamp signalSentTimeStamp = Clock::get_current_time();

        // Wait until the echo pin gets set to low (so pin_get() is false)
        while(pin_get(echo)) {
            // Time difference between now and sending the signal is larger than the timeout
            if ((Clock::get_current_time() - signalSentTimeStamp) > echoTimeout) {
                return errorLength;
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
            return errorLength;
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
