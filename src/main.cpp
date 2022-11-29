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
void competition_initialize() {
	selector::init();

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
	bool flywheelState = false;
	bool intakeState = false;
	bool intakeReverse = false;
	bool rotateDrive = true; // true means left intake is forward, false means shooter is forward. 

	int flywheelSpeed = 350;
	int flywheelSpeedIncrement = 100;

	//set ground motor brakemode to coasting, meaning that it will inertially continue
	lf_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rf_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rb_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lb_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	//intake stuff
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	//display current set flywheel rpm on controller
	std::string speed = std::to_string(flywheelSpeed);
	master.set_text(0, 0, "Speed: " + speed);
	if (rotateDrive) {
		master.set_text(0, 12, "R");
	} else {
		master.set_text(0, 12, "F");
	}
	while (true) {
		puncherPiston.set_value(puncherState);
		/*
		//get hue for color spinny thing
		double hue = color_sense.get_hue();
		double proximity = color_sense.get_proximity();
		if(proximity >= 220){
			//also for spinning, we need to place our optical sensor quite early to fight delay
			//conditionals for if robot is red team or not, check globals.hpp for this variable
			if(red_team){
				if(isRed(hue)) {
					spinner_motor.move(0);
				}
				else{
					spinner_motor.move(127);
				}
			}
			else {
				if(isRed(hue)) {
					spinner_motor.move(127);
				}
				else {
					spinner_motor.move(0);
				}
			}
		}
		*/

		//rotate to the correct goal when the button DIGITAL_A is pressed
		if (master.get_digital_new_press(DIGITAL_A) && !moveDrive) {
			translate(location.x, location.y, false, false);
			if (red_team) {
				rotate(get_angle(redGoal.x, redGoal.y));
			} else {
				rotate(get_angle(blueGoal.x, blueGoal.y));
			}
			moveDrive = true;
		}

		//flywheel warmup speed
		if (master.get_digital_new_press(DIGITAL_B)) {
			//toggle flywheel
			flywheelState = !flywheelState;
		}

		//flywheel high-gear speed
		if (flywheelState) {
			if (master.get_digital(DIGITAL_L2)) {
				setFlywheelRPM(flywheelSpeed);
			} else {
				setFlywheelRPM(200);
			}
		} else {
			setFlywheelRPM(0);
		}
		//flywheel speed modulation
		//TODO: automatic flywheel speed modulation
		if (master.get_digital_new_press(DIGITAL_UP) && flywheelSpeed <= 500 - flywheelSpeedIncrement) {
			flywheelSpeed += flywheelSpeedIncrement;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
			
		} else if (master.get_digital_new_press(DIGITAL_DOWN) && flywheelSpeed >= 200 + flywheelSpeedIncrement) {
			flywheelSpeed -= flywheelSpeedIncrement;
			//display current set flywheel rpm on controller
			speed = std::to_string(flywheelSpeed);
			master.set_text(0, 0, "Speed: " + speed);
		}
		


		//puncher control for shooting
		if (master.get_digital_new_press(DIGITAL_R2) && !puncherState) {
			puncherState = true;
			puncherTimer = 10;
			puncherPiston.set_value(puncherState);
		}
		if (puncherState) {
			puncherTimer--;
			if (puncherTimer == 0) {
				puncherState = false;
				puncherPiston.set_value(!puncherState);
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
			expansionPiston.set_value(false);
		}

		//roller mechanism control
		if (master.get_digital_new_press(DIGITAL_LEFT)) {
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
