#include "main.h"
#include "globals.hpp"
#include "odometry.hpp"
#include "autons.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}


void autonomous() {
	/*
	selector::auton == 1 : Red left
	selector::auton == 2 : Red right
	selector::auton == 3 : Do Nothing
	selector::auton == -1 : Blue left
	selector::auton == -2 : Blue right
	selector::auton == -3 : Do Nothing
	selector::auton == 0 : Skills
	*/
	pros::Task odometry(odometryLooper, "odometry");
	pros::Task motion(position_control, "motion");

	autonomousState = true;
	moveDrive = true;

	if (selector::auton == 1) {
		redLeft();
	}
	else if (selector::auton == 2) {
		redRight();
	}
	
	else if (selector::auton == -1) {
		blueLeft();
	}
	else if (selector::auton == -2) {
		blueRight();
	}
	else if (selector::auton == 0) {
		skills();
	}
}


void opcontrol() {

	while (true) {
		
		pros::delay(20);
	}
}
