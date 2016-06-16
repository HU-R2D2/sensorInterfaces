//! \addtogroup 0017 SensorInterfaces
//! \brief Interface for sensors
//!
//! One of the interfaces that need to be defined early on are the interfaces  
//! for the various types of sensors. One of the aspirations of 
//! R2D2 is modularity and for that we need to define the interface for sensors
//! like DistanceSensors, PositionSensors and SpeedSensors. 
//!
//! \file   UltrasonicSensor.hpp
//! \author Mathijs van Bremen - 1665553
//! \date   Created: 20-04-2016
//! \date   Last Modified: 13-06-2016
//! \brief  Interface for an Ultrasonic Sensor, a sensor that measures distances
//!
//! Interface for an Ultrasonic Sensor, a sensor that measures distances
//! Sensor returns a PolarView or a r2d2::Length depending on the method called
//! Interface is specifically designed for the Ping)) Ultrasonic Distance 
//! Sensor, but can be made abstract in a future project
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht. 
//! All rights reserved.
//! 
//! License: newBSD
//!
//! Redistribution and use in source and binary forms, 
//! with or without modification, are permitted provided that 
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice, 
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice, 
//!   this list of conditions and the following disclaimer in the documentation 
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht 
//!   nor the names of its contributors may be used to endorse or promote 
//!   products derived from this software without specific prior written 
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

#ifndef _ULTRASONIC_SENSOR_HPP
#define _ULTRASONIC_SENSOR_HPP

#include "LocatedDistanceSensor.hpp"
#include "Length.hpp"
#include "Speed.hpp"
#include "Clock.hpp"
#include "TimeStamp.hpp"
#include "MapPolarView.hpp"
#include "CoordinateAttitude.hpp"
#include "hwlib.h"

// If we want to compile this code on a system supported by hwlib, then we have 
// to uncomment the define below. There's a check for this define in 
// "get_distance()" that will throw an exception if not defined. This way the 
// code will also be able to compile on non-supported hwlib systems.
// #define HWLIB_ENABLED

#include <exception>

namespace r2d2 {
    //! \class OutOfRangeException
    //! \brief Exception called when result of reading was out of range
    class OutOfRangeException : public std::exception {
        virtual const char* what() const throw() {
            return "Out of range";
        }
    };

    //! \class ReadingFailedException
    //! \brief Exception called when reading failed
    class ReadingFailedException : public std::exception {
        virtual const char* what() const throw() {
            return "Reading failed";
        }
    };

    //! \class UltrasonicSensor
    //! \brief Interface for an Ultrasonic Sensor, a sensor that measures 
    //! distances
    class UltrasonicSensor : public LocatedDistanceSensor {
        public:
            //! \brief Constructs an Ultrasonic Sensor with a certain error
            //! factor, CoordinateAttitude and the pins being used
            //!
            //! \param error_factor The error factor of this sensor
            //! \param coordinate_attitude CoordinateAttitude of this sensor
            //! \param signal The pin used for the signal
            //! \param echo The pin used for the echo
            UltrasonicSensor (
                double error_factor,
                CoordinateAttitude coordinate_attitude,
                int signal,
                int echo
            );

            //! \brief Method to get the current distance from the sensor
            //!
            //! \return DistanceSensor::SensorResult SensorResult containing a 
            //! PolarView
            DistanceSensor::SensorResult get_data() override;

            //! \brief Method to get the current distance from the sensor
            //! 
            //! \throws OutOfRangeException Exception thrown when the sensor
            //! reading was out of range
            //! \throws ReadingFailedException Exception thrown when the sensor
            //! reading failed
            //! \return Length Length class containing the distance found to the
            //! object
            Length get_distance() throw(OutOfRangeException, 
                ReadingFailedException);

            //! \brief Method to set the current temperature
            //! 
            //! Temperature that is set will be used in calculating the distance
            //! when a reading has been started
            void set_temperature(double temperature);

            //! \brief Method that returns the set temperature
            //! 
            //! \return double The temperature that has been set
            double get_temperature();

        private:
            //! The pin used for the signal
            int signal;
            //! The pin used for the echo
            int echo;
            //! The last TimeStamp that there was a sensor reading
            // NOTE: TimeStamp should be 0, not current time. This will result 
            // in first 200 us not being able to use this sensor. For now we use
            // this
            TimeStamp lastReadingTimeStamp = Clock::get_current_time();
            //! Store the temperature used for calculating speed of sound 
            //! (default of 0)
            double temperature = 0.0;
            
            //! Timeout after which we will throw an exception as sensor 
            //! readings should have a minimum delay before next measurement of 
            //! 200 us
            const Duration minimumReadingInterval = 
                Duration(200 * Duration::MICROSECOND);
            //! Timeout of sending / receiving an echo after which we will 
            //! throw an exception
            const Duration echoTimeout = Duration(50 * Duration::MILLISECOND);
            //! The input trigger pulse time in us to start a reading
            const int inputTriggerPulseTime = 5;
            //! The echo holdoff time in us we wait for burst to start.
            //! Note that this value is defined as 750 in the datasheet, but we 
            //! use 700 to make sure we don't miss the return pulse
            const int echoHoldoffTime = 700;
            //! The minimum distance in cm that the sensor can read
            const Length minimumReadingDistance = 2 * Length::CENTIMETER;
            //! The maximum distance in cm that the sensor can read
            const Length maximumReadingDistance = 330 * Length::CENTIMETER;
            //! The speed of sound constant used to calculate the speed of sound 
            //! in dry (0% humidity) air
            const double speedOfSoundConstant = 331.3;
            //! The temperature coefficient used to calculate the speed of sound 
            //! in dry (0% humidity) air
            const double temperatureCoefficient = 0.606;
    };
}
#endif //_ULTRASONIC_SENSOR_HPP
