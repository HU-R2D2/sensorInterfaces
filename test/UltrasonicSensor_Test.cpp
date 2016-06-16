#include "gtest/gtest.h"
#include "../source/include/UltrasonicSensor.hpp"

using namespace r2d2;

TEST(UltrasonicSensor, LinearMeasurements) {
    UltrasonicSensor uss{ 0.1, CoordinateAttitude{},0,0 };
    // Needed as the last time is set when constructing the object
	 TimeStamp ts = Clock::get_current_time();
	 while (Clock::get_current_time() - ts < 210 * Duration::MICROSECOND);
    Length l = uss.get_distance();
	 ts = Clock::get_current_time();
    ASSERT_FALSE(l > 1 * Length::CENTIMETER);
    ASSERT_FALSE(l < 1 * Length::CENTIMETER);
	 while (Clock::get_current_time() - ts < 210 * Duration::MICROSECOND);
    l = uss.get_distance();
	 ts = Clock::get_current_time();
    ASSERT_FALSE(l > 2 * Length::CENTIMETER);
    ASSERT_FALSE(l < 2 * Length::CENTIMETER);
	 while (Clock::get_current_time() - ts < 210 * Duration::MICROSECOND);
    l = uss.get_distance();
    ASSERT_FALSE(l > 3 * Length::CENTIMETER);
    ASSERT_FALSE(l < 3 * Length::CENTIMETER);
}

TEST(UltrasonicSensor, TooFastMeasuring) {
    UltrasonicSensor uss{ 0.1, CoordinateAttitude{},0,0 };
    // Needed as the last time is set when constructing the object
	 TimeStamp ts = Clock::get_current_time();
	 while (Clock::get_current_time() - ts < 210 * Duration::MICROSECOND);
    Length l = uss.get_distance();
	 // Don't wait to trigger reading exception
    ASSERT_FALSE(l > 4 * Length::CENTIMETER);
    ASSERT_FALSE(l < 4 * Length::CENTIMETER);
    ASSERT_THROW(uss.get_distance(), ReadingFailedException);
}