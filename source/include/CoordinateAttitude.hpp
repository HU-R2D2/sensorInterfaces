//! \addtogroup 0017 SensorInterfaces
//! \brief Interface for sensors
//!
//! One of the interfaces that need to be defined early on are the interfaces  
//! for the various types of sensors. One of the aspirations of 
//! R2D2 is modularity and for that we need to define the interface for sensors
//! like DistanceSensors, PositionSensors and SpeedSensors. 
//!
//! \file   CoordinateAttitude.hpp
//! \author Alexander Freeman, Mathijs van Bremen - 1665553
//! \date   Created: 10-06-2016
//! \date   Last Modified: 15-06-2016
//! \brief  Interface for class that combines a Coordinate and an Attitude
//!
//! This class was written to combine a Coordinate and an Attitude. This 
//! class should actually be under ADTs, but at the time of writing there
//! was no time to do so. 
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

#ifndef COORDINATEATTITUDE_HPP
#define COORDINATEATTITUDE_HPP

#include "Coordinate.hpp"
#include "Attitude.hpp"
#include "Length.hpp"

namespace r2d2 {
    //! \class CoordinateAttitude
    //! \brief Interface that will just store a Coordinate and an Attitude
    class CoordinateAttitude {
        public:
            //! \brief Constructs a default CoordinateAttitude that will hold
            //! default Coordinate and default Attitude.
            CoordinateAttitude() :
                coordinate(0*Length::METER,0*Length::METER,0*Length::METER),
                attitude()
            {}
            
            //! \brief Constructs a CoordinateAttitude that will hold given
            //! Coordinate and Attitude.
            //!
            //! \param coordinate The Coordinate to store in this class
            //! \param attitude The Attitude to store in this class
            CoordinateAttitude(Coordinate coordinate, Attitude attitude) :
                coordinate(coordinate),
                attitude(attitude)
            {}

            //! \brief Method that returns the set Coordinate
            //! 
            //! \return Coordinate The Coordinate that has been set
            Coordinate get_coordinate() { return coordinate; }
            
            //! \brief Method that returns the set Attitude
            //! 
            //! \return Attitude The Attitude that has been set
            Attitude get_attitude() { return attitude; }
        private:
            //! The Coordinate that will be stored in this class
            Coordinate coordinate;
            // The Attitude that will be stored in this class
            Attitude attitude;
    };
}

#endif //COORDINATEATTITUDE_HPP
