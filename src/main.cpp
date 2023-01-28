#include "main.h"
#include "globals.hpp"
#include "helperFuncs.hpp"
#include "autons.hpp"
#include "odometry.hpp"
#include "pros/misc.h"
#include "FlywheelImplementation.hpp"
#include <string>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	expansionPiston.set_value(false);
	selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}


void autonomous() {
	initSpinUp();

	/*
	selector::auton == 1 : Red left
	selector::auton == 2 : Red right
	selector::auton == 3 : Do Nothing
	selector::auton == -1 : Blue left
	selector::auton == -2 : Blue right
	selector::auton == -3 : Do Nothing
	selector::auton == 0 : Skills
	DEFAULT IS 1
	*/

	autonomousState = true;
	moveDrive = true;

	// redLeft();
	// redRight();
	// blueLeft();
	// blueRight();
	// skills();
	
	// reminders
	// use either redLeft or blueLeft
	// pros mu to upload
	selector::auton = 0;

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
	initSpinUp();

	autonomousState = false;
	moveDrive = false;
	bool flywheelState = true;
	bool intakeState = false;
	bool intakeReverse = false;
	bool revDrive = false; // DEFAULT IS FORWARD, intake pointing forward
	int puncherCount = 0;
	int puncherDelay = 0;

	angler1Piston.set_value(false);

	int fbPower, turnPower;

	int flywheelSpeed = 300;
	//int flywheelSpeedIncrement = 50;

	//display current set flywheel rpm on controller
	std::string speed = std::to_string(flywheelSpeed);
	if (revDrive) {
		master.set_text(0, 0, "Speed: " + speed + "  R");
	} else {
		master.set_text(0, 0, "Speed: " + speed + "  F");
	}
	while (true) {

		//rotate to the correct goal when the button DIGITAL_A is pressed
		if (master.get_digital_new_press(DIGITAL_A) && !moveDrive) {
			translate(location.x, location.y, false, false);
			if (red_team) {
				rotate( get_angle(redGoal.x, redGoal.y));
			} else {
				rotate(get_angle(blueGoal.x, blueGoal.y));
			}
			moveDrive = true;
		}

		// //flywheel warmup speed
		// if (master.get_digital_new_press(DIGITAL_B)) {
		// 	//toggle flywheel
		// 	flywheelState = !flywheelState;
		// }

		//flywheel speed
		if (flywheelState) {
			setFlywheelRPM(flywheelSpeed);
		} else {
			setFlywheelRPM(0);
		}
		//flywheel speed modulation
		//TODO: automatic flywheel speed modulation
		if (master.get_digital_new_press(DIGITAL_UP) && flywheelSpeed <= 300) {
			if (flywheelSpeed == 300) flywheelSpeed = 350;
			else if (flywheelSpeed == 275) flywheelSpeed = 300;
			else if (flywheelSpeed == 250) flywheelSpeed = 275;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
			
		} else if (master.get_digital_new_press(DIGITAL_DOWN) && flywheelSpeed >= 275) {
			if (flywheelSpeed == 350) flywheelSpeed = 300;
			else if (flywheelSpeed == 300) flywheelSpeed = 275;
			else if (flywheelSpeed == 275) flywheelSpeed = 250;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
		}
		

		//intake control
		if (master.get_digital_new_press(DIGITAL_R1)) {
			if (!intakeState) intakeState = true;
			else if (intakeState && !intakeReverse) intakeState = false;
			intakeReverse = false;
		}
		// else if (master.get_digital_new_press(DIGITAL_R1)) {
		// 	if (!intakeState) intakeState = true;
		// 	else if (intakeState && intakeReverse) intakeState = false;
		// 	intakeReverse = true;
		// }
		

		//puncher control for shooting
		if (master.get_digital(DIGITAL_R2)) {
			intake.move_velocity(-127);
		} else if (intakeState) {
			if (intakeReverse) {
				intake.move(-127);
			} else {
				intake.move(127);
			}
		} else {
			intake.move(0);
		}

		if (master.get_digital(DIGITAL_L1)) {
			angler1Piston.set_value(1);
		} else if (master.get_digital(DIGITAL_L2)) {
			//low position
		} else {
			angler1Piston.set_value(0);
		}

		//drive rotation
		if (master.get_digital_new_press(DIGITAL_X)) {
			revDrive = !revDrive;
			if (revDrive) {
			master.set_text(0, 12, "R");
			} else {
				master.set_text(0, 12, "F");
			}
		}
		

		//expansion control
		if ((master.get_digital(DIGITAL_Y) && master.get_digital_new_press(DIGITAL_RIGHT))
			|| (master.get_digital(DIGITAL_RIGHT) && master.get_digital_new_press(DIGITAL_Y))) {
			expansionPiston.set_value(true);
		} else {
			expansionPiston.set_value(false);
		}

		fbPower = master.get_analog(ANALOG_LEFT_Y);
		turnPower = master.get_analog(ANALOG_RIGHT_X);

		if (abs(fbPower) < 10) {
			fbPower = 0;
		}
		if (abs(turnPower) < 10) {
			turnPower = 0;
		}

		fbPower = (pow(abs(fbPower), powerFactor) / pow(127, powerFactor - 1) * sgn(fbPower));
		turnPower = (pow(abs(turnPower), powerFactor) / pow(127, powerFactor - 1) * sgn(turnPower));

		if (abs(fbPower) > 10 || abs(turnPower) > 10) {
			moveDrive = false;
		}

		if (revDrive) {
			fbPower = -fbPower;
		}

		if (!moveDrive) {
			l1_motor.move(fbPower + turnPower);
			l2_motor.move(fbPower + turnPower);
			l3_motor.move(fbPower + turnPower);
			r1_motor.move(fbPower - turnPower);
			r2_motor.move(fbPower - turnPower);
			r3_motor.move(fbPower - turnPower);
		}

		pros::delay(20);
	}
}
