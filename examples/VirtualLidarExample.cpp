//! \addtogroup 0038 VirtualSensors
//! \brief VirtualSensors simulating physical sensors
//!
//! \file   VirtualLidarExample.cpp
//! \author Jeroen Steendam 1607288
//! \date   Created: 15/6/2016
//! \date   Last Modified: 16/6/2016
//! \brief  Example file using a VirtualLidar
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

#include "../source/include/VirtualLidar.hpp"
#include "LockingSharedObject.hpp"
#include "RStarMap.hpp"

// ostream operator for std::unique_ptr<PolarView>
std::ostream& operator<<(
        std::ostream& os,
        const std::unique_ptr<r2d2::PolarView>& polarView) {

    for(int i = 0; i < 360; ++i) {
        os << i*r2d2::Angle::deg << ": ";
        r2d2::DistanceReading reading =
                polarView->get_distance(i*r2d2::Angle::deg);
        os << reading.get_length() << " ";
        r2d2::DistanceReading::ResultType resType = reading.get_result_type();
        switch(resType) {
        case r2d2::DistanceReading::ResultType::CHECKED:
            std::cout << "[CHECKED]";
            break;
        case r2d2::DistanceReading::ResultType::DIDNT_CHECK:
            std::cout << "[DIDNT_CHECK]";
            break;
        case r2d2::DistanceReading::ResultType::OUT_OF_RANGE:
            std::cout << "[OUT_OF_RANGE]";
            break;
        };
        std::cout << std::endl;
    }
    return os;
}

// Test file for map
const std::string file_name = "test.map";

// Create test map with two obstacles
r2d2::RStarMap createMap() {
    r2d2::RStarMap map;

    // Add obstacle at (2, 2, 0)(5, 5, 2)
    map.set_box_info(
        r2d2::Box(
            r2d2::Coordinate(
                2*r2d2::Length::METER,
                2*r2d2::Length::METER,
                0*r2d2::Length::METER),
            r2d2::Coordinate(
                5*r2d2::Length::METER,
                5*r2d2::Length::METER,
                2*r2d2::Length::METER)
        ),
        r2d2::BoxInfo(true, false, false));

    // Add obstacle at (-2, -5, 0)(-3, -5.5, 2)
    map.set_box_info(
        r2d2::Box(
            r2d2::Coordinate(
                -2*r2d2::Length::METER,
                -5*r2d2::Length::METER,
                0*r2d2::Length::METER),
            r2d2::Coordinate(
                -3*r2d2::Length::METER,
                -5.5*r2d2::Length::METER,
                2*r2d2::Length::METER)
            ),
        r2d2::BoxInfo(true, false, false));

    // Save the map
    map.save(file_name);
    return map;
}


// Creates a test map if it doesn't exist yet
// Then returns the map
r2d2::RStarMap getMap() {
    // check if exists
    std::fstream file;
    file.open(file_name);
    if(file.is_open()) {
        file.close();
        r2d2::RStarMap map;
        map.load(file_name);
        return map;
    }
    return createMap();
}

int main() {
    r2d2::RStarMap map;
    map.load(file_name);

    LockingSharedObject<r2d2::ReadOnlyMap> sharedObject(map);

    r2d2::Coordinate coordinate(
                -3 * r2d2::Length::METER,
                3 * r2d2::Length::METER,
                1 * r2d2::Length::METER);
    r2d2::CoordinateAttitude position(coordinate, r2d2::Attitude());
    r2d2::VirtualLidar lidar(sharedObject, position);
    r2d2::DistanceSensor::SensorResult result = lidar.get_data();

    std::unique_ptr<r2d2::PolarView> polarView = result.get_value();
    std::cout << polarView << std::endl;

    return 0;
}
