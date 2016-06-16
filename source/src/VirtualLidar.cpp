//! \addtogroup 0038 Virtual Sensors
//! \brief Two implementations of virtual sensors.
//!
//! If physical sensors are not available these virtual sensor can be used.
//!
//! \file   VirtualLidar.cpp
//! \author Jeroen Steendam 1607288
//! \date   Created: 09-06-2016
//! \date   Last Modified: 09-06-2016
//! \brief  VirtualLidar simulates a physical lidar using a Map.
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

#include "../include/VirtualLidar.hpp"
#include "Box.hpp"
#include "MapPolarView.hpp"

#include <cmath>
#include <limits>

r2d2::VirtualLidar::VirtualLidar(
        LockingSharedObject<ReadOnlyMap>& map,
        const CoordinateAttitude& position) :
    LocatedDistanceSensor(0, position),
    map(map)
{
}

r2d2::DistanceSensor::SensorResult r2d2::VirtualLidar::get_data() {
    std::unique_ptr<PolarView> polarView(new r2d2::MapPolarView());

    // Lock map, unlocks automatically at end of scope
    LockingSharedObject<ReadOnlyMap>::Accessor accessor(map);

    Coordinate origin = coordinate_attitude.get_coordinate();

    // Scan 360 degrees
    //
    // Calculate new point from point and vector
    // x = start_x + len * cos(angle);
    // y = start_y + len * sin(angle);
    //
    // angle must be in radians so
    // radians = degrees*(PI/180)
    for(int angle = 0; angle < 360; angle++) {
        Coordinate p(
                    origin.get_x() + max_range*std::cos(angle*(M_PI/180)),
                    origin.get_y() + max_range*std::sin(angle*(M_PI/180)),
                    origin.get_z());

        Coordinate lastCoordinate = coordinate_attitude.get_coordinate();

        double totalSteps = max_range/accuracy;

        // Follow laser from begin to end with stepsize accuracy and check if
        // there is an obstacle
        for (int j = 1; j <= totalSteps; j++) {
            Length subLength = j*accuracy;

            // Calculate new point on line with distance subLength
            Coordinate newCoordinate(
                        origin.get_x() + subLength*std::cos(angle*(M_PI/180)),
                        origin.get_y() + subLength*std::sin(angle*(M_PI/180)),
                        origin.get_z());

            Box fieldToCheck(lastCoordinate, newCoordinate);
            BoxInfo boxInfo = accessor.access().get_box_info(fieldToCheck);

            if(boxInfo.get_has_obstacle()) {
                polarView->add_distancereading(
                            angle * Angle::deg,
                            DistanceReading(
                                subLength,
                                DistanceReading::ResultType::CHECKED));
                break;
            }
            else if(j == totalSteps) {
                polarView->add_distancereading(
                            angle * Angle::deg,
                            DistanceReading(
                                -1 * Length::METER,
                                DistanceReading::ResultType::OUT_OF_RANGE));
            }

            lastCoordinate = newCoordinate;
        }
    }

    return r2d2::DistanceSensor::SensorResult(0, polarView);
}
