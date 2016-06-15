//! \addtogroup 0017 SensorInterfaces
//! \brief Interface for sensors
//!
//! One of the interfaces that need to be defined early on are the interfaces  
//! for the various types of sensors. One of the aspirations of 
//! R2D2 is modularity and for that we need to define the interface for sensors
//! like DistanceSensors, PositionSensors and SpeedSensors. 
//!
//! \file   UltrasonicSensorTestCode.cpp
//! \author Mathijs van Bremen - 1665553
//! \date   Created: 08-04-2016
//! \date   Last Modified: 15-06-2016
//! \brief  Test code for sensor interfaces (mainly Ultrasonic Sensor)
//!
//! This code will test the Ultrasonic Sensor and show how to use the sensor. 
//! It will just keep reading the distance from the Ultrasonic Sensor as long as
//! the program is running.
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

#include "../include/UltrasonicSensor.hpp"
#include "../include/CoordinateAttitude.hpp"

#include <iostream>

// The define below will be used to check whether or not we are on a hwlib
// supported system or not. If not, then hwlib related methods won't be 
// used. This way the code will be able to compile on non-supported hwlib
// systems as well.
// #define HWLIB_ENABLED

#ifdef HWLIB_ENABLED
#include "hwlib.c"
#endif

#include "MapPolarView.hpp"
#include "DistanceReading.hpp"


int main() {
    int signal_pin = 0;
    int echo_pin = 0;
    
    // If HWLIB_ENABLED was defined, we can call some methods specific for hwlib
    #ifdef HWLIB_ENABLED
    bcm2835_init();
    signal_pin = RPI_V2_GPIO_P1_18;
    echo_pin = RPI_V2_GPIO_P1_18;
    #endif

    // Create a CoordinateAttitude, used by UltrasonicSensor
    r2d2::CoordinateAttitude coord_attitude = r2d2::CoordinateAttitude();
    // Create an UltrasonicSensor
    r2d2::UltrasonicSensor u(
        0, coord_attitude, signal_pin, echo_pin);
    
    while(true) {
        // Get the PolarView from the SensorResult (returned by get_data())
        std::unique_ptr<r2d2::PolarView> polarView = u.get_data().get_value();

        // Get the DistanceReading from the PolarView at the set yaw
        r2d2::DistanceReading distanceReading = 
            polarView->get_distance(coord_attitude.get_attitude().get_yaw());

        // According to the ResultType we print something in the console
        if (distanceReading.get_result_type() == 
            r2d2::DistanceReading::ResultType::CHECKED) {

            std::cout << distanceReading.get_length() << std::endl;

        } else if (distanceReading.get_result_type() ==
            r2d2::DistanceReading::ResultType::DIDNT_CHECK) {

            std::cout << "=== Reading failed ===" << std::endl;

        } else {

            std::cout << "=== Out of range ===" << std::endl;
        }
    }
    
    return 0;
}
