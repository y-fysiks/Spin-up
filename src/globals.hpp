#include "main.h"

#ifndef CONFIG_HPP
#define CONFIG_HPP

//------------------------------------------------------------------------------
// Port configuration
#define PI 3.14159265358979323
#define lf_motor_port 4
#define rf_motor_port 3
#define lb_motor_port 2
#define rb_motor_port 1
#define conveyor_motor_port 5
#define roller_flex_port 20
#define intake_port 6
#define intake_port_2 11
//switch this if needed
#define optical_port 19
#define imu_port 10
// ADI ports
#define left_tracking_port_top 1
#define left_tracking_port_bottom 2
#define right_tracking_port_top 3
#define right_tracking_port_bottom 4
#define rear_tracking_port_top 5
#define rear_tracking_port_bottom 6
// Odometry constants
#define WHEEL_DIST_LR 13.35
#define XWHEEL_DIST_CENTER -6.1

//------------------------------------------------------------------------------
//Global PROS objects and variables
//Motors
pros::Motor lf_motor(lf_motor_port, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rf_motor(rf_motor_port, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor lb_motor(lb_motor_port, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor rb_motor(rb_motor_port, MOTOR_GEARSET_18, true,MOTOR_ENCODER_DEGREES);
pros::Motor spinner_motor(roller_flex_port, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor intake_1(intake_port, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
pros::Motor intake_2(intake_port_2, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
//Sensors
pros::Imu imu(imu_port);
pros::Optical color_sense(optical_port);
//controller
pros::Controller master(CONTROLLER_MASTER);
//pneumatics
//autonomous state indicator

//------------------------------------------------------------------------------
//GREATAPI objects and variables
//sensors
greatapi::TWheel* right_encoder = new greatapi::TWheel_ADIEncoder(right_tracking_port_top, right_tracking_port_bottom, false, 2.75);
greatapi::TWheel* left_encoder = new greatapi::TWheel_ADIEncoder(left_tracking_port_top, left_tracking_port_bottom, false, 2.75);
greatapi::TWheel* rear_encoder = new greatapi::TWheel_ADIEncoder(rear_tracking_port_top, rear_tracking_port_bottom, false, 2.75);
//odometry object
greatapi::odometry::TWheel_odom_rotation odomRotation = *new greatapi::odometry::TWheel_odom_rotation(left_encoder, right_encoder, WHEEL_DIST_LR);
greatapi::odometry::odometry odom(rear_encoder, greatapi::inches(XWHEEL_DIST_CENTER), right_encoder, greatapi::inches(WHEEL_DIST_LR / 2.0), &odomRotation);

//global location object (VERY IMPORTANT!!!)
greatapi::position location(greatapi::coord(0, 0), greatapi::SRAD());
//total position error
double total_error = 0;
double speedCap = 12000;

//defines which auton to run
bool skillsAuton = true;

//------------------------------------------------------------------------------
//other variables
bool moveDrive = true;
bool autonomousState = false;
bool red_team = true;

#endif // CONFIG_HPP