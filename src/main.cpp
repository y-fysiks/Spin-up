#include "main.h"
#include "globals.hpp"
#include "helperFuncs.hpp"
#include "autons.hpp"
#include "progSkills.hpp"
#include "odometry.hpp"
#include "motionAlgos.hpp"
#include "FlywheelImplementation.hpp"
#include "pros/rtos.hpp"
#include <string>
#include <utility>

bool expandLowerFW = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	expansionPiston.set_value(false);
	angler1Piston.set_value(false);
	selector::init();
	imuRotation.Inertial.reset();
	pros::delay(2200);
	expandLowerFW = false;
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
	selector::auton == 3 : Solo AWP
	selector::auton == -1 : Blue left
	selector::auton == -2 : Blue right
	selector::auton == -3 : Solo AWP
	selector::auton == 0 : Skills
	DEFAULT IS 1
	*/

	autonomousState = true;
	moveDrive = true;

	// initAuton(greatapi::SRAD(0));
	// pros::delay(100);

	//std::pair<double, double> path1[] = {std::make_pair(0, 40), std::make_pair(40, 40)};

	// rtranslatevl(0, 30, false, 6000, false, false, 0);
	// translatevl(0, 0, true, 6000, false, false, 0);
	//pros::delay(10000);

	//ptranslatevl(path1, 2, false, 8000, false, false, 0);
	
	// pros mu to upload
	
	selector::auton = 1;

	if (selector::auton == 1) {
		redLeft();
	} else if (selector::auton == 2) {
		redRight();
	} else if (selector::auton == -1) {
		redLeft();
	} else if (selector::auton == -2) {
		redRight();
	} else if (selector::auton == 3) {
		soloAWP();
	} else if (selector::auton == -3) {
		soloAWP();
	} else if (selector::auton == 0) {
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
	bool revDrive = false; // DEFAULT IS FORWARD, intake pointing forward
	bool precMode = false;
	bool rollerSlow = false;
	int rumbleCounter = 0;

	bool intakeOverride = false;

	int discFullTimer = 0;
	int fourthDiskTimer = 0;

	int fbPower, turnPower;

	int flywheelSpeed = 350;

	//display current set flywheel rpm on controller
	std::string speed = std::to_string(flywheelSpeed);
	if (revDrive) {
		master.set_text(0, 0, "Speed: " + speed);
	} else {
		master.set_text(0, 0, "Speed: " + speed);
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

		//flywheel speed
		//TODO: automatic flywheel speed modulation
		if (master.get_digital_new_press(DIGITAL_UP)) {
			if (flywheelSpeed + 10 <= 600) {
				flywheelSpeed += 10;
			}
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
			
		} else if (master.get_digital_new_press(DIGITAL_DOWN)) {
			if (flywheelSpeed - 10 >= 0) {
				flywheelSpeed -= 10;
			}
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
		}

		if (master.get_digital(DIGITAL_LEFT)) flywheelState = false;
		else flywheelState = true;
		
		if (flywheelState) {
			setFlywheelRPM(flywheelSpeed);
		} else {
			setFlywheelRPM(0);
		}
		
		if (discFullSensor.get_value() < 2300) {
			if (discFullTimer < 100000000) discFullTimer++;
		} else {
			discFullTimer = 0;
			intakeReverse = false;
			intakeOverride = false;
		}
		if (discFullTimer > 300 / 20) {
			//if the disc reservoir is full, stop the intake
			if (!intakeOverride) intakeReverse = true;
		}

		//intake control
		if (master.get_digital_new_press(DIGITAL_R1)) {
			if (!intakeState) intakeState = true;
			else if (intakeState && !intakeReverse) intakeState = false;
			intakeReverse = false;
			if (discFullTimer > 500 / 20) {
				intakeOverride = true;
			}
		}
		if (master.get_digital(DIGITAL_L1)) {
			intake.move(-127);
		} else {
			if (intakeState) {
				if (intakeReverse) {
					intake.move(-127);
				} else {
					intake.move(127);
				}
			} else {
				intake.move(0);
			}
		}

		//indexer control for shooting
		if (master.get_digital(DIGITAL_R2)) {
			tripleIndexerPiston.set_value(true);
		} else {
			tripleIndexerPiston.set_value(false);
		}

		if (master.get_digital(DIGITAL_L2)) {
			singleIndexerPiston.set_value(true);
		} else {
			singleIndexerPiston.set_value(false);
		}
		
		

		

		// if (fourthDiskSensor.get_value() < 2500) {
		// 	if (fourthDiskTimer < 100000000) fourthDiskTimer++;
		// } else {
		// 	fourthDiskTimer = 0;
		// }

		// if (master.get_digital(DIGITAL_L2)) {
		// 	//shooting precision mode
		// 	precMode = true;
		// 	l1_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// 	l2_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// 	l3_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// 	r1_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// 	r2_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// 	r3_motor.set_brake_mode(MOTOR_BRAKE_HOLD);
		// } else {
		// 	precMode = false;
		// 	l1_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// 	l2_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// 	l3_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// 	r1_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// 	r2_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// 	r3_motor.set_brake_mode(MOTOR_BRAKE_COAST);
		// }

		//drive rotation
		// if (master.get_digital_new_press(DIGITAL_X)) {
		// 	revDrive = !revDrive;
		// 	if (revDrive) {
		// 	master.set_text(0, 12, "R");
		// 	} else {
		// 		master.set_text(0, 12, "F");
		// 	}
		// }
		
		if ((master.get_digital(DIGITAL_Y) || master.get_digital(DIGITAL_RIGHT))) {
			intake.move(-127);
			angler1Piston.set_value(false);
		} else if (master.get_digital(DIGITAL_B) || expandLowerFW) {
			angler1Piston.set_value(false);
		} else {
			angler1Piston.set_value(true);
		}

		//expansion control
		if ((master.get_digital(DIGITAL_Y) && master.get_digital(DIGITAL_RIGHT))) {
			expansionPiston.set_value(true);
			expandLowerFW = true;

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
