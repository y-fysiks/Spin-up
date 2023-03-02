#include "autons.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    initAuton(greatapi::SRAD(PI));

    setFlywheelRPM(487);
    //intake.move(127);
    pros::delay(100);

    //roller
    translate(0, -10, false, false, false);
    pros::delay(300);
    intake.move_relative(1150, 600);
    pros::delay(550);
    intake.move(0);
    translate(0, 5, true, false, false, 0);

    //shoot 2 discs
    rotate(180 - 10.5, 0);
    pros::delay(200);
    shoot(2, 600);
    pros::delay(200);

    //set rpm for second volley
    setFlywheelRPM(473);
    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    translatevl(40, 33, false, 10000, true, false, 25);
    translatevl(40, 33, false, 5000, true, false, 0);

    //move back a bit
    translate(30, 26, true, false, false, 0);

    //second volley
    rotate(180 - 26, 0);
    angler1Piston.set_value(false);
    pros::delay(200);
    shoot(3, 550);
    angler1Piston.set_value(true);

    //intake discs for third volley
    intake.move(127);
    rtranslatevl(4, -10, false, 6000, true, false, 3);
    rtranslatevl(-2, -10, false, 5000, true, false, 0);
    rtranslate(-1, 30, true, false, false, 0);

    intake.move(0);
    //third volley
    angler1Piston.set_value(false);
    rotate(180 - 24, 0);
    pros::delay(200);
    shoot(3, 550);
    angler1Piston.set_value(true);

}

void redRight() {
    //red right
    initAuton(greatapi::SRAD(0));

    setFlywheelRPM(490);

    rtranslate(0, 5, true, false, false, 0);
    rotate(180 + 12, 0);
    pros::delay(3600);
    shoot(2);
    intake.move(127);
    rtranslate(-38, 38, false, true, false, 0);
    intake.move(0);
    rotate(180 + 42, 0);
    shoot(3);
    translate(7, 5, false, true, false, 0);
    rtranslate(0, -30, false, true, false);
    intake.move_relative(-1080, 600);
    pros::delay(2000);
    moveDrive = false;

}

void blueLeft() {//
    //blue left
}

void blueRight() {
    //blue right
    red_team = false;
}

void soloAWP() {
    initAuton(greatapi::SRAD(PI));

    setFlywheelRPM(490);
    //intake.move(127);
    pros::delay(100);
    translate(0, -10, false, false, false);
    pros::delay(200);
    intake.move_relative(1150, 600);
    pros::delay(503);
    intake.move(0);
    translate(0, 5, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 10.5, 0);
    pros::delay(600);
    shoot(2);
    pros::delay(250);
    setFlywheelRPM(478);
    //rtranslate(1, -1, false, false, false, 0);
    //rotate(45, 0);
    angler1Piston.set_value(true);
    intake.move(127);
    translatevl(40, 33, false, 5500, true, false, 0);

    rotate(180 - 29.5, 0);
    angler1Piston.set_value(false);
    pros::delay(300);


    //-------------SIMILARITY WITH RED LEFT ENDS HERE----------------

    fastShoot();
    
    intake.move(127);
    translatevl(108, 72, false, 12000, true, false, 0);
    intake.move(0);
    translatevl(115, 70, false, 10000, false, false);

    //rtranslate(3, 0, false, true, false);
    pros::delay(400);
    intake.move_relative(1200, 600);
    pros::delay(500);
    intake.move(0);
}