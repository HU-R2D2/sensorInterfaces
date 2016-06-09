////                                                                                                                                        
// Roborescue
//
// \file UltrasonicSensor.hpp
// \date Created: 08-04-16
// \version 0.2.0
//
// \author Mathijs van Bremen
//
// \section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////

#ifndef _ULTRASONIC_SENSOR_HPP
#define _ULTRASONIC_SENSOR_HPP

#include "LocatedDistanceSensor.hpp"
#include "hwlib.h"
#include "Length.hpp"
#include "Speed.hpp"
#include "Clock.hpp"
#include "TimeStamp.hpp"


namespace r2d2 {

class UltrasonicSensor : public LocatedDistanceSensor {
    
    public:
        UltrasonicSensor (
            double error_factor,
            int coordinate_attitude,
            int signal, 
            int echo
        );
        
        //get_data() override;
        
        Length get_distance();
        
        void set_temperature(double temperature);
        double get_temperature();
        
    private:
        // The pin used for the signal
        int signal;
        // The pin used for the echo
        int echo;
        // The last TimeStamp that there was a sensor reading
        TimeStamp lastReadingTimeStamp;
        // Store the temperature used for calculating speed of sound (default of 0)
        double temperature = 0.0;
        
        // Timeout after which we will return an error as sensor readings should have a minimum delay before next measurement of 200 us
        const Duration minimumReadingInterval = Duration(200 * Duration::MICROSECOND);
        // Timeout of sending / receiving an echo after which we will return an error
        const Duration echoTimeout = Duration(50 * Duration::MILLISECOND);
        // The errorLength we will return when something goes wrong
        const Length errorLength = -1 * Length::METER;
        // The input trigger pulse time in us to start a reading
        const int inputTriggerPulseTime = 5;
        // The echo holdoff time in us we wait for burst to start.
        // Note that this value is defined as 750 in the datasheet, but to be sure we use 700 to make sure we don't miss the return pulse
        const int echoHoldoffTime = 700;
        // The minimum distance in cm that the sensor can read
        const Length minimumReadingDistance = 2 * Length::CENTIMETER;
        // The maximum distance in cm that the sensor can read
        const Length maximumReadingDistance = 330 * Length::CENTIMETER;
        // The speed of sound constant used to calculate the speed of sound in dry (0% humidity) air
        const double speedOfSoundConstant = 331.3;
        // The temperature coefficient used to calculate the speed of sound in dry (0% humidity) air
        const double temperatureCoefficient = 0.606;
    };
}
#endif //_ULTRASONIC_SENSOR_HPP
