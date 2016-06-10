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

#include <cmath>
#include <limits>


class Point {
public:
    double x;
    double y;
    Point(double x, double y) : x(x), y(y) {}
    static double distance(const Point& a, const Point& b) {
        return std::sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
    }
};

r2d2::VirtualLidar::VirtualLidar(LockingSharedObject<ArrayBoxMap>& map, CoordinateAttitude position) :
    LocatedDistanceSensor(0, position),
    map(map)
{
}

Point calculatePointOnBoundary(Point topLeft, Point bottomRight, Point start, r2d2::Angle angle)
{
    // Calculate intersections with box walls
    double vx = std::cos(angle.get_angle());
    double vy = std::sin(angle.get_angle());

    double t1 = (topLeft.x - start.x) / vx; //left
    double t2 = (bottomRight.x - start.x) / vx; //right
    double t3 = (topLeft.y - start.y) / vy; //top
    double t4 = (bottomRight.y - start.y) / vy; //bottom

    double t = std::numeric_limits<double>::max();

    if(t1 >= 0 && t1 < t)
        t = t1;
    if(t2 >= 0 && t2 < t)
        t = t2;
    if(t3 >= 0 && t3 < t)
        t = t3;
    if(t4 >= 0 && t4 < t)
        t = t4;

    return Point(start.x+t*vx, start.y+t*vy);
}

r2d2::DistanceSensor::SensorResult r2d2::VirtualLidar::get_data()
{
    std::unique_ptr<PolarView> polarView(new MapPolarView());
    r2d2::DistanceSensor::SensorResult returnValue(0, polarView);

    // Lock map
    LockingSharedObject<ArrayBoxMap>::Accessor accessor(map);
    const Box boundingBox = accessor.access().get_map_bounding_box();
    const Point topLeft(boundingBox.get_bottom_left().get_x() / Length::METER, boundingBox.get_top_right().get_y() / Length::METER);
    const Point topRight(boundingBox.get_top_right().get_x() / Length::METER, boundingBox.get_top_right().get_y() / Length::METER);
    const Point bottomLeft(boundingBox.get_bottom_left().get_x() / Length::METER, boundingBox.get_bottom_left().get_y() / Length::METER);
    const Point bottomRight(boundingBox.get_top_right().get_x() / Length::METER, boundingBox.get_bottom_left().get_y() / Length::METER);

    Point middle(coordinate_attitude.getCoordinate().get_x() / Length::METER, coordinate_attitude.getCoordinate().get_y() / Length::METER);

    // scan 360 degrees
    for(int i = 0; i < 1; i++) {
        Point p = calculatePointOnBoundary(topLeft, bottomRight, middle, i*Angle::deg);
//        std::cout << i << ": (" << p.x << ", " << p.y << ")" << std::endl;

        double angle = i;
        double length = Point::distance(p, middle);
        std::cout << length << std::endl;
    }

    // Unlock map automatically
    return returnValue;
}
