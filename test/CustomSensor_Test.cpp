#include "gtest/gtest.h"
#include "CustomSensor.hpp"
#include <iostream>

using namespace r2d2;

TEST(CustomSensor, CustomModuloSensor) {
    std::cout << "Testing custom sensors inheriting from Sensor..." << std::endl;
    CustomModuloSensor cms(0.0);
    CustomModuloSensor::SensorResult sr = cms.get_data();
    ASSERT_EQ(sr.get_value(), 4ul);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cms.get_data();
    ASSERT_EQ(sr.get_value(), 7ul);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cms.get_data();
    ASSERT_EQ(sr.get_value(), 0ul);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cms.get_data();
    ASSERT_EQ(sr.get_value(), 3ul);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cms.get_data();
    ASSERT_EQ(sr.get_value(), 6ul);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
}

TEST(CustomSensor, CustomIncementalSensor) {
    CustomIncementalSensor cis(0.0);
    CustomIncementalSensor::SensorResult sr = cis.get_data();
    ASSERT_EQ(sr.get_value(), 1);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cis.get_data();
    ASSERT_EQ(sr.get_value(), 2);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cis.get_data();
    ASSERT_EQ(sr.get_value(), 3);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cis.get_data();
    ASSERT_EQ(sr.get_value(), 4);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cis.get_data();
    ASSERT_EQ(sr.get_value(), 5);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
}

TEST(CustomSensor, CustomDecrementalSensor) {
    CustomDecrementalSensor cds(0.0);
    CustomDecrementalSensor::SensorResult sr = cds.get_data();
    ASSERT_EQ(sr.get_value(), -1);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cds.get_data();
    ASSERT_EQ(sr.get_value(), -2);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cds.get_data();
    ASSERT_EQ(sr.get_value(), -3);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cds.get_data();
    ASSERT_EQ(sr.get_value(), -4);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
    sr = cds.get_data();
    ASSERT_EQ(sr.get_value(), -5);
    ASSERT_DOUBLE_EQ(sr.get_error_factor(), 0.0);
}