#include "lemlib/api.hpp"

//Intialize Motor Groups for Drive and Intake
extern pros::MotorGroup top_down_roller;
extern pros::MotorGroup left_motor_group;
extern pros::MotorGroup right_motor_group;

extern lemlib::Drivetrain  drivetrain;
extern lemlib::Chassis chassis;

// Initalize sensor
extern lemlib::OdomSensors sensors;
extern pros::Imu imu;

// Initialize controller + settings
extern pros::Controller controller;

// Initialize the pistons Pistons
extern pros::adi::Pneumatics piston1;
extern pros::adi::Pneumatics piston2;
