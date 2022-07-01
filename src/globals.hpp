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
#define roller_flex_port 20
#define intake_port 6
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
inline pros::Motor lf_motor(lf_motor_port, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
inline pros::Motor rf_motor(rf_motor_port, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
inline pros::Motor lb_motor(lb_motor_port, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
inline pros::Motor rb_motor(rb_motor_port, MOTOR_GEARSET_18, true,MOTOR_ENCODER_DEGREES);
inline pros::Motor spinner_motor(roller_flex_port, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
inline pros::Motor intake(intake_port, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);
//Sensors
inline pros::Imu imu(imu_port);
inline pros::Optical color_sense(optical_port);
//controller
inline pros::Controller master(CONTROLLER_MASTER);
//pneumatics
//autonomous state indicator

//------------------------------------------------------------------------------
//GREATAPI objects and variables
//sensors
inline greatapi::TWheel* right_encoder = new greatapi::TWheel_ADIEncoder(right_tracking_port_top, right_tracking_port_bottom, false, 2.75);
inline greatapi::TWheel* left_encoder = new greatapi::TWheel_ADIEncoder(left_tracking_port_top, left_tracking_port_bottom, false, 2.75);
inline greatapi::TWheel* rear_encoder = new greatapi::TWheel_ADIEncoder(rear_tracking_port_top, rear_tracking_port_bottom, false, 2.75);
//odometry object
inline greatapi::odometry::TWheel_odom_rotation odomRotation = *new greatapi::odometry::TWheel_odom_rotation(left_encoder, right_encoder, WHEEL_DIST_LR);
inline greatapi::odometry::odometry odom(rear_encoder, greatapi::inches(XWHEEL_DIST_CENTER), right_encoder, greatapi::inches(WHEEL_DIST_LR / 2.0), &odomRotation);

//global location object (VERY IMPORTANT!!!)
inline greatapi::position location(greatapi::coord(0, 0), greatapi::SRAD());
//total position error
inline double total_error = 0;
inline double speedCap = 12000;

//defines which auton to run
inline bool skillsAuton = true;

//------------------------------------------------------------------------------
//other variables
inline bool moveDrive = true;
inline bool autonomousState = false;
inline bool red_team = true;

#endif // CONFIG_HPP