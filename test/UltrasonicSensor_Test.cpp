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


#include <iostream>
TEST(CustomSensor, CustomModuloSensor) {
	std::cout << "Testing custom sensors inheriting from Sensor..." << std::endl;
	CustomModuloSensor cms(0.0);
	CustomModuloSensor::SensorResult sr = cms.get_data();
	ASSERT_EQ(sr.get_value(), 4ul);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cms.get_data();
	ASSERT_EQ(sr.get_value(), 7ul);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cms.get_data();
	ASSERT_EQ(sr.get_value(), 0ul);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cms.get_data();
	ASSERT_EQ(sr.get_value(), 3ul);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cms.get_data();
	ASSERT_EQ(sr.get_value(), 6ul);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
}

TEST(CustomSensor, CustomIncementalSensor) {
	CustomIncementalSensor cis(0.0);
	CustomIncementalSensor::SensorResult sr = cis.get_data();
	ASSERT_EQ(sr.get_value(), 1);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cis.get_data();
	ASSERT_EQ(sr.get_value(), 2);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cis.get_data();
	ASSERT_EQ(sr.get_value(), 3);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cis.get_data();
	ASSERT_EQ(sr.get_value(), 4);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cis.get_data();
	ASSERT_EQ(sr.get_value(), 5);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
}

TEST(CustomSensor, CustomDecrementalSensor) {
	CustomDecrementalSensor cds(0.0);
	CustomDecrementalSensor::SensorResult sr = cds.get_data();
	ASSERT_EQ(sr.get_value(), -1);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cds.get_data();
	ASSERT_EQ(sr.get_value(), -2);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cds.get_data();
	ASSERT_EQ(sr.get_value(), -3);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cds.get_data();
	ASSERT_EQ(sr.get_value(), -4);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
	sr = cds.get_data();
	ASSERT_EQ(sr.get_value(), -5);
	ASSERT_EQ(sr.get_error_factor(), 0.0);
}