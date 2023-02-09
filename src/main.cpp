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
	
	selector::auton = 1;

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
	
    pros::screen::set_eraser(COLOR_BLACK);
    pros::screen::erase();

	autonomousState = false;
	moveDrive = false;
	bool flywheelState = true;
	bool intakeState = false;
	bool intakeReverse = false;
	bool revDrive = true; // DEFAULT IS FORWARD, intake pointing forward
	bool precMode = false;
	bool rollerSlow = false;

	int fbPower, turnPower;

	int flywheelSpeed = 370;

	//display current set flywheel rpm on controller
	std::string speed = std::to_string(flywheelSpeed);
	if (revDrive) {
		master.set_text(0, 0, "Speed: " + speed + "  R");
	} else {
		master.set_text(0, 0, "Speed: " + speed + "  F");
	}
	while (true) {
		//rotate to the correct goal when the button DIGITAL_A is pressed
		// if (master.get_digital_new_press(DIGITAL_A) && !moveDrive) {
		// 	//translate(location.x, location.y, false, false);
		// 	if (red_team) {
		// 		//rotate( get_angle(redGoal.x, redGoal.y));
		// 	} else {
		// 		//rotate(get_angle(blueGoal.x, blueGoal.y));
		// 	}
		// 	moveDrive = true;
		// }

		// //flywheel warmup speed
		// if (master.get_digital_new_press(DIGITAL_B)) {
		// 	//toggle flywheel
		// 	flywheelState = !flywheelState;
		// }

		angler1Piston.set_value(true);

		//flywheel speed
		flywheelState = true;
		if (flywheelState) {
			setFlywheelRPM(flywheelSpeed);
		} else {
			setFlywheelRPM(0);
		}
		//flywheel speed modulation
		//TODO: automatic flywheel speed modulation
		if (master.get_digital_new_press(DIGITAL_UP)) {
			if (flywheelSpeed == 425) flywheelSpeed = 500;
			else if (flywheelSpeed == 360) flywheelSpeed = 425;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
			
		} else if (master.get_digital_new_press(DIGITAL_DOWN)) {
			if (flywheelSpeed == 500) flywheelSpeed = 425;
			else if (flywheelSpeed == 425) flywheelSpeed = 360;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
		}

		if (master.get_digital_new_press(DIGITAL_LEFT)) {
			flywheelState = !flywheelState;
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
			intake.move(-127);
		} else if (rollerSlow) {
			intake.move_velocity(350);
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
			rollerSlow = true;
		} else {
			rollerSlow = false;
		}
		if (master.get_digital(DIGITAL_L2)) {
			//shooting precision mode
			precMode = true;
			l1_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
			l2_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
			l3_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
			r1_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
			r2_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
			r3_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		} else {
			precMode = false;
			l1_motor.set_brake_mode(MOTOR_BRAKE_COAST);
			l2_motor.set_brake_mode(MOTOR_BRAKE_COAST);
			l3_motor.set_brake_mode(MOTOR_BRAKE_COAST);
			r1_motor.set_brake_mode(MOTOR_BRAKE_COAST);
			r2_motor.set_brake_mode(MOTOR_BRAKE_COAST);
			r3_motor.set_brake_mode(MOTOR_BRAKE_COAST);
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
		if ((master.get_digital(DIGITAL_Y) && master.get_digital(DIGITAL_RIGHT))) {
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

		// if (abs(fbPower) > 10 || abs(turnPower) > 10) {
		// 	moveDrive = false;
		// }

		if (revDrive) {
			fbPower = -fbPower;
		}

		if (precMode) turnPower *= 0.28;

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
