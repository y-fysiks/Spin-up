#include "main.h"

#ifndef CONFIG_HPP
#define CONFIG_HPP

//------------------------------------------------------------------------------
// Port configuration
#define PI 3.1415926535897932384626433832795
#define lf_motor_port 3
#define rf_motor_port 1
#define lb_motor_port 4
#define rb_motor_port 2
#define intake_port 8
#define flywheel_port_1 5
#define flywheel_port_2 6
#define optical_port 19
#define imu_port 10
#define puncher_port 'A'
// Tracking wheel ports
#define left_tracking_port 10
#define right_tracking_port 11
#define rear_tracking_port 12
// Odometry constants
#define WHEEL_DIST_LR 13.1
#define XWHEEL_DIST_CENTER -0.5

//------------------------------------------------------------------------------
// Global PROS objects and variables
// Motors
inline pros::Motor lf_motor(lf_motor_port, MOTOR_GEARSET_06, true,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor rf_motor(rf_motor_port, MOTOR_GEARSET_06, false,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor lb_motor(lb_motor_port, MOTOR_GEARSET_06, true,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor rb_motor(rb_motor_port, MOTOR_GEARSET_06, false,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor intake(intake_port, MOTOR_GEARSET_36, false,
                          MOTOR_ENCODER_DEGREES);
inline pros::Motor flywheel_1(flywheel_port_1, MOTOR_GEARSET_06, false,
                              MOTOR_ENCODER_DEGREES);
inline pros::Motor flywheel_2(flywheel_port_2, MOTOR_GEARSET_06, true,
                                MOTOR_ENCODER_DEGREES);
// Sensors
inline pros::Imu imu(imu_port);
inline pros::Optical color_sense(optical_port);
// controller
inline pros::Controller master(CONTROLLER_MASTER);
// pneumatics
inline pros::ADIDigitalOut puncher(puncher_port);
// autonomous state indicator

//------------------------------------------------------------------------------
// GREATAPI objects and variables
// sensors
inline greatapi::TWheel *right_encoder =
    new greatapi::TWheel_RotationSensor(right_tracking_port, false, 3.25);
inline greatapi::TWheel *left_encoder =
    new greatapi::TWheel_RotationSensor(left_tracking_port, false, 3.25);
inline greatapi::TWheel *rear_encoder =
    new greatapi::TWheel_RotationSensor(rear_tracking_port, false, 3.25);
// odometry object
inline greatapi::odometry::TWheel_odom_rotation odomRotation =
    *new greatapi::odometry::TWheel_odom_rotation(left_encoder, right_encoder,
                                                  WHEEL_DIST_LR);
inline greatapi::odometry::odometry
    odom(rear_encoder, greatapi::inches(XWHEEL_DIST_CENTER), right_encoder,
         greatapi::inches(WHEEL_DIST_LR / 2.0), &odomRotation);

// global location object (VERY IMPORTANT!!!)
inline greatapi::position location(greatapi::coord(0, 0), greatapi::SRAD(0));
// this is the target position for the robot to try to reach
inline greatapi::position targetPos(greatapi::coord(0, 0), greatapi::SRAD(0));
// total position error
inline double total_error = 0;
//voltage cap to reduce speed
inline double voltageCap = 12000;

//goal locations
inline greatapi::position blueGoal(greatapi::coord(0, 0), greatapi::SRAD(0));
inline greatapi::position redGoal(greatapi::coord(0, 0), greatapi::SRAD(0));

//------------------------------------------------------------------------------
// other variables
inline bool moveDrive = true;
inline bool autonomousState = false;
inline bool red_team = true;
inline bool puncherState = false;
inline int puncherTimer = 0;

#endif // CONFIG_HPP
