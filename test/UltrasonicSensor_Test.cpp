#include "gtest/gtest.h"
#include "../source/include/Sensor.hpp"

using namespace r2d2;

// Unable to test Sensor, DistanceSensor, and LocatedDistanceSensor functionality on its own as these contain a pure virtual function

TEST(SensorResult, Ints) {
	int value{ 12 };
	Sensor<int>::SensorResult s{ 0.0, value };
	ASSERT_EQ(s.get_value(), 12);
	ASSERT_EQ(s.get_error_factor(), 0.0);

	value = { 15 };
	s = { 1.0, value };
	ASSERT_EQ(s.get_value(), 15);
	ASSERT_EQ(s.get_error_factor(), 1.0);
}

TEST(SensorResult, Floats) {
	float value{ 0.123f };
	Sensor<float>::SensorResult s{ 0.0, value };
	ASSERT_EQ(s.get_value(), 0.123f);
	ASSERT_EQ(s.get_error_factor(), 0.0);

	value = { 0.123f };
	s = { 1.0, value };
	ASSERT_EQ(s.get_value(), 0.123f);
	ASSERT_EQ(s.get_error_factor(), 1.0);
}
