//! \addtogroup 0038 Virtual Sensors
//! \brief Two implementations of virtual sensors.
//!
//! If physical sensors are not available these virtual sensor can be used.
//!
//! \file   VirtualUltrasonicSensor.hpp
//! \author Jeroen Steendam 1607288
//! \date   Created: 09-06-2016
//! \date   Last Modified: 09-06-2016
//! \brief  VirtualUltrasonicSensor simulates a physical ultrasonic sensor using a Map.
//!
//! <Detailed description of file>
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

#ifndef VIRTUALULTRASONICSENSOR_H
#define VIRTUALULTRASONICSENSOR_H

#include "LocatedDistanceSensor.hpp"
#include "LockingSharedObject.hpp"
#include "RStarMap.hpp"

namespace r2d2 {

class VirtualUltrasonicSensor : public LocatedDistanceSensor {
public:
    VirtualUltrasonicSensor(
            LockingSharedObject<RStarMap>& map,
            const CoordinateAttitude& position);

   DistanceSensor::SensorResult get_data();
private:
    LockingSharedObject<RStarMap>& map;
    const Length accuracy = 0.1 * Length::METER;
    const Length max_range = 4 * Length::METER;
};

}

#endif //VIRTUALULTRASONICSENSOR_H
