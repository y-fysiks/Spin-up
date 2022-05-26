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

	//initialize controller, then set ground motor brakemode to coasting, meaning that it will inertially continue
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	left_front_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_front_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_rear_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_rear_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	//I think this is the one that immidiatley stops the motor
	spinner_motor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true) {
		//get hue for color spinny thing
		double hue = color_sense.get_hue();
		double proximity = color_sense.get_proximity();
		if(proximity >= 220){
			//also for spinning, we need to place our optical sensor quite early to fight delay
			//conditionals for if robot is red team or not, check globals.hpp for this variable
			if(red_team){
				if(isRed(hue)){
					spinner_motor.move(0);
				}
				else{
					spinner_motor.move(127);
				}
			}
			else{
				if(isRed(hue)){
					spinner_motor.move(127);
				}
				else{
					spinner_motor.move(0);
				}
			}
		}
		//get turn, left right, front back values for movement in x drive, then move motors accordingly using diagram below
		//http://fabacademy.org/2019/labs/kannai/students/kota-tomaru/images/final/wheelpatterns.jpg
		int front_back = round(master.get_analog(ANALOG_RIGHT_Y));
		int left_right = round(master.get_analog(ANALOG_RIGHT_X));
		int turn = round(master.get_analog(ANALOG_LEFT_X));
		left_front_mtr.move(front_back - left_right + turn);
		left_rear_mtr.move(front_back + left_right  + turn);
		right_front_mtr.move(front_back + left_right - turn);
		right_rear_mtr.move(front_back - left_right - turn);
		pros::delay(20);
	}
}
