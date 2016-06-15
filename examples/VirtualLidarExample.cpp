#include "../source/include/VirtualLidar.hpp"
#include "LockingSharedObject.hpp"

// ostream operator for std::unique_ptr<PolarView>
std::ostream& operator<<(
        std::ostream& os,
        const std::unique_ptr<r2d2::PolarView>& polarView) {

    for(int i = 0; i < 360; i++) {
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
    using namespace r2d2;
    r2d2::RStarMap map;
    map.load(file_name);

    LockingSharedObject<r2d2::RStarMap> sharedObject(map);

    r2d2::Coordinate coordinate(-3*r2d2::Length::METER, 3*r2d2::Length::METER, 1*r2d2::Length::METER);
    r2d2::CoordinateAttitude position(coordinate, r2d2::Attitude());
    r2d2::VirtualLidar lidar(sharedObject, position);
    r2d2::DistanceSensor::SensorResult result = lidar.get_data();

    std::unique_ptr<r2d2::PolarView> polarView = result.get_value();
    std::cout << polarView << std::endl;

    return 0;
}
