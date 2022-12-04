#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    red_team = true;
    //31.75, 9

    // pros::delay(10000);

    // rtranslate(0, -2, false, false);
    // pros::delay(500);
    // roller.move_relative(-90, 100);
    // setFlywheelRPM(380);
    // pros::delay(1000);
    // rtranslate(4, 12, false, false, 0);
    // rotate(-13, 0);
    // pros::delay(500);
    // shoot(2);
    setFlywheelRPM(400);
    pros::delay(3000);
    shoot(2);
    lf_motor.move_relative(150, 300);
    rf_motor.move_relative(-150, 300);
    rb_motor.move_relative(-150, 300);
    lb_motor.move_relative(150, 300);
    pros::delay(1000);
    lf_motor.move_relative(-100, 300);
    rf_motor.move_relative(100, 300);
    rb_motor.move_relative(-100, 300);
    lb_motor.move_relative(100, 300);
    pros::delay(1000);
    lf_motor.move(-127);
    rf_motor.move(-127);
    lb_motor.move(-127);
    rb_motor.move(-127);
    pros::delay(1000);
    roller.move_relative(-90, 100);


}

void redRight() {
    //red right
    red_team = true;
}

void blueLeft() {
    //blue left
    // red_team = false;
    // rtranslate(0, 2, false, false);
    // pros::delay(500);
    // roller.move_relative(90, 100);
    // pros::delay(1000);
    // setFlywheelRPM(400);
    // rtranslate(-3, -6, false, false, 0);
    // rotate(-13 + 180, 0);
    // pros::delay(500);
    // shoot(2);
}

void blueRight() {
    //blue right
    red_team = false;
}

void skills() {
    //skills RED TEAM
    red_team = true;
    //red left
    moveDrive = true;
    //31.75, 9
    rtranslate(0, -2, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(380);
    pros::delay(1000);
    rtranslate(4, 12, false, false, 0);
    rotate(-13, 0);
    pros::delay(500);
    shoot(2);
    setFlywheelRPM(200);
    intake.move(-127);
    translate(20, 28, false, false, 0);
    rotate(90, 0);
    translate(9, 28, false, false, 0.5);
    rtranslate(-2, 0, false, false, 0);
    pros::delay(500);
    roller.move_relative(-90, 100);
    pros::delay(1000);


    //get into pos for expansion
    translate(20, 20, true, false, 0);
    rotate(-135);
    expansionPiston.set_value(1);

}