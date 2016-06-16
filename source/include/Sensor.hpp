//! \addtogroup 0017 SensorInterfaces
//! \brief Interface for sensors
//!
//! One of the interfaces that need to be defined early on are the interfaces  
//! for the various types of sensors. One of the aspirations of 
//! R2D2 is modularity and for that we need to define the interface for sensors
//! like DistanceSensors, PositionSensors and SpeedSensors. 
//!
//! \file   Sensor.hpp
//! \author Mathijs van Bremen - 1665553
//! \date   Created: 20-04-2016
//! \date   Last Modified: 13-06-2016
//! \brief  Interface for sensors: base class of all sensors
//!
//! This is the base class for all sensors. To use this class you should define 
//! the template used by this Sensor. This template class will then be returned
//! by the get_data() method which should be overridden.
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

#ifndef _SENSOR_HPP
#define _SENSOR_HPP

#include <memory>

namespace r2d2 {
    template<class T>
    
    //! \class Sensor
    //! \brief Interface for a sensor
    class Sensor {

        public:
            //! \brief Constructs a Sensor with a certain error factor
            //!
            //! \param factor The error factor of this sensor
            Sensor(double factor):
            error_factor{ factor }
            {}

            //! \class SensorResult
            //! \brief SensorResult containing an error factor and a value of 
            //! the defined template
            class SensorResult {
                public:
                    //! \brief Constructs a SensorResult with a certain error
                    //! factor and a value of the defined template
                    //!
                    //! \param error_factor The error factor of this sensor
                    //! \param value The value of defined template of the result
                    SensorResult(double error_factor, T& value) :
                        error_factor{ error_factor },
                        value{ std::move(value) }
                    {}

                    //! \brief Method to get the error factor distance from the 
                    //! sensor
                    //!
                    //! \return double The error factor that has been set
                    double get_error_factor() { return error_factor; }

                    //! \brief Method to get the value from the sensor
                    //!
                    //! \return T The value of defined template that has been 
                    //! set
                    T get_value() { return std::move(value); }

                private:
                    //! The error factor of this sensor
                    double error_factor;
                    //! The value of defined template of this SensorResult
                    T value;
            };

            //! \brief Method to get the data from the sensor
            //!
            //! \return SensorResult SensorResult from this specific sensor
            virtual SensorResult get_data() = 0;

        protected:
            //! The error factor of this sensor
            double error_factor;

    };
}

#endif //_SENSOR_HPP
