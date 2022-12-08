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
	location.x = 0; location.y = 0; location.angle = greatapi::SRAD(0);
	//selector::init();
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
	bool rotateDrive = false; // DEFAULT TO FLYWHEEL IS FORWARD
	int puncherCount = 0;

	int flywheelSpeed = 300;
	//int flywheelSpeedIncrement = 50;

	//display current set flywheel rpm on controller
	std::string speed = std::to_string(flywheelSpeed);
	if (rotateDrive) {
		master.set_text(0, 0, "Speed: " + speed + "  R");
	} else {
		master.set_text(0, 0, "Speed: " + speed + "  R");
	}
	while (true) {
		puncherPiston.set_value(puncherState);

		//rotate to the correct goal when the button DIGITAL_A is pressed
		if (master.get_digital_new_press(DIGITAL_A) && !moveDrive) {
			translate(location.x, location.y, false, false);
			if (red_team) {
				rotate(2 * PI - get_angle(redGoal.x, redGoal.y));
			} else {
				rotate(2 * PI - get_angle(blueGoal.x, blueGoal.y));
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
		


		//puncher control for shooting
		if (master.get_digital_new_press(DIGITAL_R2) && !puncherState) {
			puncherCount = 1;
		}
		if (master.get_digital(DIGITAL_L2)) {
			puncherCount = 4;
		}
		if (puncherCount > 0) {
			puncherCount --;
			puncherState = true;
			puncherTimer = 10;
			puncherPiston.set_value(puncherState);
		}
		if (puncherState) {
			puncherTimer--;
			if (puncherTimer == 0) {
				puncherState = false;
				puncherPiston.set_value(puncherState);
			}
		}

		//intake control
		if (master.get_digital_new_press(DIGITAL_L1)) {
			if (!intakeState) intakeState = true;
			else if (intakeState && !intakeReverse) intakeState = false;
			intakeReverse = false;
		} else if (master.get_digital_new_press(DIGITAL_R1)) {
			if (!intakeState) intakeState = true;
			else if (intakeState && intakeReverse) intakeState = false;
			intakeReverse = true;
		}
		if (intakeState) {
			if (intakeReverse) {
				intake.move(-127);
			} else {
				intake.move(127);
			}
		} else {
			intake.move(0);
		}

		//drive rotation
		if (master.get_digital_new_press(DIGITAL_X)) {
			rotateDrive = !rotateDrive;
			if (rotateDrive) {
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

		//roller mechanism control
		if (master.get_digital(DIGITAL_LEFT)) {
			roller.move(-127);
		}
		else {
			roller.move(0);
		}
		
		
		//get turn, left right, front back values for movement in x drive, then move motors accordingly using diagram below
		//http://fabacademy.org/2019/labs/kannai/students/kota-tomaru/images/final/wheelpatterns.jpg
		int front_back = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		front_back = (pow(abs(front_back), powerFactor) / pow(127, powerFactor - 1) * sgn(front_back));
		left_right = (pow(abs(left_right), powerFactor) / pow(127, powerFactor - 1) * sgn(left_right));
		turn = (pow(abs(turn), powerFactor) / (pow(127, powerFactor - 1)) * sgn(turn)) * 0.7;

		if (abs(front_back) > 10 || abs(left_right) > 10 || abs(turn) > 10) {
			moveDrive = false;
		}
		if (rotateDrive) {
			int temp = left_right;
			left_right = -front_back;
			front_back = temp;
		}

		if (!moveDrive) {
			lf_motor.move(front_back + left_right + turn);
			rf_motor.move(front_back - left_right - turn);
			lb_motor.move(front_back - left_right + turn);
			rb_motor.move(front_back + left_right - turn);
		}

		pros::delay(20);
	}
}
