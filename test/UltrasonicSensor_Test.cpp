#include "gtest/gtest.h"
#include "../source/include/UltrasonicSensor.hpp"

using namespace r2d2;

//static UltrasonicSensor* u = nullptr;
//
//TEST(UltrasonicSensor, Initialization) {
//u = new UltrasonicSensor(0.0f, 0, 0, 0);
//}
//
//TEST(UltrasonicSensor, DistanceTests) { // Get_distance() starts at 2 and is multiplied by two everytime it gets called
//r2d2::Length l = u->get_distance();
//ASSERT_LT(l, 2.1f * r2d2::Length::CENTIMETER);
//ASSERT_GT(l, 1.9f * r2d2::Length::CENTIMETER);
//l = u->get_distance();
//ASSERT_LT(l, 4.1f * r2d2::Length::CENTIMETER);
//ASSERT_GT(l, 3.9f * r2d2::Length::CENTIMETER);
//l = u->get_distance();
//ASSERT_LT(l, 8.1f * r2d2::Length::CENTIMETER);
//ASSERT_GT(l, 7.9f * r2d2::Length::CENTIMETER);
//}
//
//TEST(UltrasonicSensor, Cleanup) {
//delete u;
//u = nullptr;
//}