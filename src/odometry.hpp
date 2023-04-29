#include "main.h"
#include "globals.hpp"
#include "pros/colors.h"

#ifndef ODOMETRY_HPP

#define ODOMETRY_HPP

#define kPAngle 18000
#define kIAngle 7000

inline greatapi::controlelement *PY = new greatapi::Proportional(1200, std::pair(__INT_MAX__, -__INT_MAX__));          
inline greatapi::controlelement *IY = new greatapi::Integral(0, std::pair(3000, -3000));                              
inline greatapi::controlelement *DY = new greatapi::Derivative(1800, std::pair(__INT_MAX__, -__INT_MAX__));            

inline greatapi::controlelement *PAngle = new greatapi::Proportional(kPAngle, std::pair(__INT_MAX__, -__INT_MAX__));     
inline greatapi::controlelement *IAngle = new greatapi::Integral(kIAngle, std::pair(1000, -1000));                        
inline greatapi::controlelement *DAngle = new greatapi::Derivative(320000, std::pair(__INT_MAX__, -__INT_MAX__));       

/**
 * odometry function
 * 
 */
void odometryLooper();

/**
 * function to be run in a task to move the robot the the target position
 * 
 */
void position_control();

/**
 * rotates the bot to the specified absolute heading. Blocks execution until the bot is at the specified heading.
 * 
 * \param angle the absolute heading to rotate to
 * \param errorStop DEGREES the function will stop the bot if the error is greater than the error threshold. IF 0, default is 3 degrees
 */
void rotate(double angleDeg, double errorStop);

/**
 * translates the robot to absolute coordinates. Blocks execution. 
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param maxVoltage the maximum voltage to send to the motors
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target
 * \param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.3
 */
void translate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading);

void translate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock);

void translatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading);

void translatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock);


void rtranslate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading);

void rtranslate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock);

void rtranslatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading);

void rtranslatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock);


void rtranslateDist(double dist, bool revDrive, double maxVoltage);
void rtranslateDist(double dist, bool revDrive);

#endif