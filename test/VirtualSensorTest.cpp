#include "gtest/gtest.h"

#include "../source/include/VirtualLidar.hpp"
#include "ArrayBoxMap.hpp"

#include <memory>

TEST(VirtualLidarTest, GetData)
{
    using namespace r2d2;
    // TODO: write test
    ArrayBoxMap map;
    map.set_box_info(Box(Coordinate(0*Length::METER, 2*Length::METER, 0*Length::METER),Coordinate(2*Length::METER, 0*Length::METER, 2*Length::METER)), BoxInfo());
//    std::cout << map.get_map_bounding_box().get_axis_size().get_x() << std::endl;
//    std::cout << map.get_map_bounding_box().get_axis_size().get_y() << std::endl;
//    std::cout << map.get_map_bounding_box().get_axis_size().get_z() << std::endl;

//    std::cout << map.get_map_bounding_box().get_bottom_left().get_x() << std::endl;
//    std::cout << map.get_map_bounding_box().get_bottom_left().get_y() << std::endl;
//    std::cout << map.get_map_bounding_box().get_top_right().get_x() << std::endl;
//    std::cout << map.get_map_bounding_box().get_top_right().get_y() << std::endl;
    LockingSharedObject<ArrayBoxMap> sharedObject(map);
    Coordinate coordinate(1*Length::METER, 1*Length::METER, 1*Length::METER);
//    std::cout << "Start: (" << coordinate.get_x() / Length::METER << ", " << coordinate.get_y() / Length::METER << ")" << std::endl;
    CoordinateAttitude position(coordinate, Attitude());
//    std::cout << "Start: (" << position.getCoordinate().get_x() / Length::METER << ", " << position.getCoordinate().get_y() / Length::METER << ")" << std::endl;
    VirtualLidar lidar(sharedObject, position);
    DistanceSensor::SensorResult result = lidar.get_data();
    ASSERT_TRUE(true);
}

TEST(VirtualUltrasonicSensorTest, GetData)
{
    // TODO: write test
    ASSERT_TRUE(true);
}
