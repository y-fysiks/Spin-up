#include "main.h"

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
	selector::auton == 1 : Red Front
	selector::auton == 2 : Red Back
	selector::auton == 3 : Do Nothing
	selector::auton == -1 : Blue Front
	selector::auton == -2 : Blue Back
	selector::auton == -3 : Do Nothing
	selector::auton == 0 : Skills
	*/

	if (selector::auton == 1) {
	}
	else if (selector::auton == 2) {
	}
	
	else if (selector::auton == -1) {
	}
	else if (selector::auton == -2) {
	}
	else if (selector::auton == 0) {
	}
}


void opcontrol() {

	while (true) {
		
		pros::delay(20);
	}
}
