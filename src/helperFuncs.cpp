#include "main.h"
#include "globals.hpp"
#include "odometry.hpp"
#include "pros/colors.h"
#include "pros/screen.hpp"

/**
 * Set flywheel speed (both motors)
 * 
 * \param speed speed in rpm (-100 - 600)
 */
void flywheel(int speed) {
    flywheel_1.move_velocity(speed);
    flywheel_2.move_velocity(speed);
}

void flywheelVoltage(int voltage) {
    flywheel_1.move_voltage(voltage);
    flywheel_2.move_voltage(voltage);
}

void initSpinUp() {
    //erase screen, deletes all auton selector stuff
    pros::screen::set_eraser(COLOR_BLACK);
    pros::screen::erase();
    
	pros::Task odometry(odometryLooper, "odometry");
	pros::Task motion(position_control, "motion");

    if (selector::auton == 1) {
		red_team = true;
        location = redLStart;
	} else if (selector::auton == 2) {
		red_team = true;
        location = redRStart;
	} else if (selector::auton == -1) {
		red_team = false;
        location = blueLStart;
	} else if (selector::auton == -2) {
		red_team = false;
        location = blueRStart;
	} else if (selector::auton == 0) {
		red_team = true; // SKILLS USES RED TEAM LEFT
        location = redLStart;
	}

    targetPos = location;
}

// functions to get angle given current position and target position
/**
 *  dot product of two vectors
 * 
 * \param a x component of first vector
 * \param b y component of first vector
 * \param c x component of second vector
 * \param d y component of second vector
 * \return result of dot product
 */
long double dot(long double a, long double b, long double c, long double d){
    return (long double)(acos(((a*c) + (b*d))/ (sqrt(a*a+b*b)* sqrt(c*c+d*d))));
    // get angle between vectors
}

/**
 *  sign function
 * 
 * \param x number to get sign of
 * \return int sign of x
 */
int sgn(long double x){
    if (x >= 0) return 1;
    // give angle as x>=0 so if its 0 degrees then it will return that its anti clockwise and print 0 instead of 2pi
    return -1;
}
// b 0 a b
// d 0 c d
/**
 *  sign of the cross product of two vectors
 * 
 * \param a x component of first vector
 * \param b y component of first vector
 * \param c x component of second vector
 * \param d y component of second vector
 * \return int sign of cross product
 */
int cross(long double a, long double b, long double c, long double d){
    return sgn(a*d- c*b);
    // see if its clockwise or counterclockwise orientation
}

/**
 *  Get the angle object
 * 
 * \param targetx x component of target vector
 * \param targety y component of target vector
 * \return long double 
 */
long double get_angle(long double targetx, long double targety){
    long double a, b, c, d;
    c = targetx-location.x; d = targety-location.y;
    a=1; b=0;
    //need to find anticlockwise direction between 2 vectors
    // dot product gives angle from first vector to second vector
    long double pi = acos(-1);
    if(cross(a, b, c, d)<0){// clockwise
        return 2*pi-dot(a, b, c, d);
    }else{// anticlockwise
        return dot(a, b, c, d);
    }
}
