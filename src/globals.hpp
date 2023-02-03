#include "main.h"
#include "pros/motors.h"

#ifndef CONFIG_HPP
#define CONFIG_HPP

//------------------------------------------------------------------------------
// Port configuration
#define PI 3.1415926535897932384626433832795
#define l1_motor_port 1 //1 is top, 3 is bottom
#define l2_motor_port 2
#define l3_motor_port 3
#define r1_motor_port 4
#define r2_motor_port 5
#define r3_motor_port 6

#define intake_port 10
#define flywheel_port_1 8
#define roller_port 13
#define optical_port 19
#define angler1_port 'A'
#define expansion_port 'B'
// Tracking wheel ports
#define left_tracking_port 11
#define right_tracking_port 12
#define rear_tracking_port 13
// Odometry constants
#define WHEEL_DIST_LR 5.6875
#define XWHEEL_DIST_CENTER -4.0

#define powerFactor 1.5

//------------------------------------------------------------------------------
// Global PROS objects and variables
// Motors
inline pros::Motor l1_motor(l1_motor_port, MOTOR_GEARSET_06, true,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor l2_motor(l2_motor_port, MOTOR_GEARSET_06, false,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor l3_motor(l3_motor_port, MOTOR_GEARSET_06, true,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor r1_motor(r1_motor_port, MOTOR_GEARSET_06, false,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor r2_motor(r2_motor_port, MOTOR_GEARSET_06, true,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor r3_motor(r3_motor_port, MOTOR_GEARSET_06, false,
                            MOTOR_ENCODER_DEGREES);
inline pros::Motor intake(intake_port, MOTOR_GEARSET_06, true,
                          MOTOR_ENCODER_DEGREES);
inline pros::Motor flywheel(flywheel_port_1, MOTOR_GEARSET_06, false,
                              MOTOR_ENCODER_DEGREES);

// Sensors
inline pros::Optical color_sense(optical_port);
// controller
inline pros::Controller master(CONTROLLER_MASTER);
// pneumatics
inline pros::ADIDigitalOut angler1Piston(angler1_port, 0);
inline pros::ADIDigitalOut expansionPiston(expansion_port, 0);

//------------------------------------------------------------------------------
// GREATAPI objects and variables
// sensors
inline greatapi::TWheel *right_encoder =
    new greatapi::TWheel_RotationSensor(right_tracking_port, false, 3.17644);
inline greatapi::TWheel *left_encoder =
    new greatapi::TWheel_RotationSensor(left_tracking_port, true, 3.17644);
inline greatapi::TWheel *rear_encoder =
    new greatapi::TWheel_RotationSensor(rear_tracking_port, false, 3.17644);
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

#define leftStartX 8.75
#define StartY 9

//goal locations, Red Left corner is 0, 0
inline greatapi::position blueGoal(greatapi::coord(124, 140 - 123), greatapi::SRAD(0));
inline greatapi::position redGoal(greatapi::coord(140 - 124, 123), greatapi::SRAD(0));
inline greatapi::position redLStart(greatapi::coord(9.75 + 23.4, StartY), greatapi::SRAD(PI));
inline greatapi::position redRStart(greatapi::coord(140 - 8, 140 - 2 * 23.4 - 9.75), greatapi::SRAD(greatapi::degrees(90)));
inline greatapi::position blueLStart(greatapi::coord(140 - 23.4 - 9.75, 140 - StartY), greatapi::SRAD(greatapi::degrees(180)));
inline greatapi::position blueRStart(greatapi::coord(StartY, 2 * 23.4 + 9.75), greatapi::SRAD(greatapi::degrees(270)));

//------------------------------------------------------------------------------
// other variables
inline bool moveDrive = true;
inline bool translating = false;
inline bool reverseDrive = false;
inline bool autonomousState = false;
inline bool red_team = true;
inline bool angler1State = false;
inline int puncherTimer = 0;
inline int alignGoal = 0; //0 = disable, 1 = red, 2 = blue

#endif // CONFIG_HPP
