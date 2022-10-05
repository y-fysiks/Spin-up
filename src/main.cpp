#include "main.h"
#include "globals.hpp"
#include "helperFuncs.hpp"
#include "autons.hpp"
#include "odometry.hpp"

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
	DEFAULT IS 1
	*/
	pros::Task odometry(odometryLooper, "odometry");
	pros::Task motion(position_control, "motion");

	autonomousState = true;
	moveDrive = true;

	if (selector::auton == 1) {
		red_team = true;
		redLeft();
	}
	else if (selector::auton == 2) {
		red_team = true;
		redRight();
	}
	
	else if (selector::auton == -1) {
		red_team = false;
		blueLeft();
	}
	else if (selector::auton == -2) {
		red_team = false;
		blueRight();
	}
	else if (selector::auton == 0) {
		red_team = true; // SKILLS USES RED TEAM
		skills();
	}
}


void opcontrol() {

	//set ground motor brakemode to coasting, meaning that it will inertially continue
	lf_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rf_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	rb_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	lb_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	//intake stuff
	intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	
	while (true) {
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
		//get turn, left right, front back values for movement in x drive, then move motors accordingly using diagram below
		//http://fabacademy.org/2019/labs/kannai/students/kota-tomaru/images/final/wheelpatterns.jpg
		int front_back = master.get_analog(ANALOG_LEFT_Y);
		int left_right = master.get_analog(ANALOG_LEFT_X);
		int turn = round(master.get_analog(ANALOG_RIGHT_X));
		lf_motor.move(front_back + left_right + turn);
		rf_motor.move(front_back - left_right - turn);
		lb_motor.move(front_back - left_right + turn);
		rb_motor.move(front_back + left_right - turn);
		pros::delay(20);
	}
}
