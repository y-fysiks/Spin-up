#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    red_team = true;
    //31.75, 9
    rtranslate(0, -2, false, false);
    pros::delay(500);
    roller.move_relative(90, 100);
    pros::delay(1000);
    setFlywheelRPM(400);
    translate(3, 6, false, false, 0);
    rotate(15, 0);
    shoot(2);
}

void redRight() {
    //red right
    red_team = true;
}

void blueLeft() {
    //blue left
    red_team = false;
    translate(0, 2, false, false);
    pros::delay(500);
    roller.move_relative(90, 100);
    pros::delay(1000);
    setFlywheelRPM(400);
    translate(-3, -6, false, false, 0);
    rotate(15 + 180, 0);
    shoot(2);
}

void blueRight() {
    //blue right
    red_team = false;
}

void skills() {
    //skills RED TEAM
    red_team = true;
}