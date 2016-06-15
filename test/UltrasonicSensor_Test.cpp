#include "gtest/gtest.h"
#include "../source/include/UltrasonicSensor.hpp"
#include <chrono>
#include <thread>

using namespace r2d2;

TEST(UltrasonicSensor, LinearMeasurements) {
	UltrasonicSensor uss{ 0.1, CoordinateAttitude{},0,0 };
	// Needed as the last time is set when constructing the object
	std::this_thread::sleep_for(std::chrono::microseconds(210));
	Length l = uss.get_distance();
	ASSERT_FALSE(l > 1 * Length::CENTIMETER);
	ASSERT_FALSE(l < 1 * Length::CENTIMETER);
	std::this_thread::sleep_for(std::chrono::microseconds(210));
	l = uss.get_distance();
	ASSERT_FALSE(l > 2 * Length::CENTIMETER);
	ASSERT_FALSE(l < 2 * Length::CENTIMETER);
	std::this_thread::sleep_for(std::chrono::microseconds(210));
	l = uss.get_distance();
	ASSERT_FALSE(l > 3 * Length::CENTIMETER);
	ASSERT_FALSE(l < 3 * Length::CENTIMETER);
}

TEST(UltrasonicSensor, TooFastMeasuring) {
	UltrasonicSensor uss{ 0.1, CoordinateAttitude{},0,0 };
	// Needed as the last time is set when constructing the object
	std::this_thread::sleep_for(std::chrono::microseconds(210));
	Length l = uss.get_distance();
	ASSERT_FALSE(l > 4 * Length::CENTIMETER);
	ASSERT_FALSE(l < 4 * Length::CENTIMETER);
	ASSERT_THROW(uss.get_distance(), ReadingFailedException);
}