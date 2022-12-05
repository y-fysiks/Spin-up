#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    red_team = true;
    //31.75, 9

    // pros::delay(10000);
    moveDrive = true;
    //31.75, 9
    rtranslate(0, -2, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(362);
    pros::delay(2000);
    rtranslate(4, 12, false, false, 0);
    rotate(-18, 0);
    pros::delay(500);
    shoot(1);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(200);
    // setFlywheelRPM(374);
    // pros::delay(3000);
    // shoot(2);
    // lf_motor.move_relative(150, 300);
    // rf_motor.move_relative(-150, 300);
    // rb_motor.move_relative(-150, 300);
    // lb_motor.move_relative(150, 300);
    // pros::delay(1000);
    // lf_motor.move_relative(-100, 300);
    // rf_motor.move_relative(100, 300);
    // rb_motor.move_relative(-100, 300);
    // lb_motor.move_relative(100, 300);
    // pros::delay(1000);
    // lf_motor.move(-127);
    // rf_motor.move(-127);
    // lb_motor.move(-127);
    // rb_motor.move(-127);
    // pros::delay(1000);
    // roller.move_relative(-90, 100);


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
    roller.move_relative(-190, 100);
    // setFlywheelRPM(357);
    pros::delay(1000);
    rtranslate(4, 12, false, false, 0);
    // rotate(-18, 0);
    // pros::delay(500);
    // shoot(1);
    // pros::delay(500);
    // shoot(2);
    setFlywheelRPM(200);
    intake.move(-127);
    translate(20, 28, false, false, 0);
    rotate(90, 0);
    translate(10, 28, false, false, 0.5);
    rtranslate(-2, 0, false, false);
    pros::delay(500);
    roller.move_relative(-190, 100);
    pros::delay(1000);
    translate(25, 25, false, false, 0);

    rotate(135, 0);
    setFlywheelRPM(300);
    translate(70.2, 70.2, 10000, false, false, 110);//134.35 total distance
    alignGoal = 2;
    shoot(3);
    setFlywheelRPM(315);
    translate(106, 106, 700, false, false, 36);
    shoot(1);
    setFlywheelRPM(330);
    translate(106, 106, 700, false, false, 18);
    shoot(1);
    setFlywheelRPM(350);
    translate(106, 106, 700, false, false, 0);
    shoot(1);
    setFlywheelRPM(270);
    translate(120, 120, false, false, 0);
    rtranslate(0, -80, false, false, 0);
    fastShoot(2);

    //get into pos for expansion
    setFlywheelRPM(0);
    translate(120, 120, true, false, 0);
    rotate(-45, 0);
    expansionPiston.set_value(1);

}