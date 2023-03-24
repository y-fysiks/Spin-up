#include "autons.hpp"

void leftStarter() {
    initAuton(greatapi::SRAD(PI));

    setFlywheelRPM(483);
    //intake.move(127);
    pros::delay(100);

    //roller
    translate(0, -10, false, false, false);
    pros::delay(300);
    intake.move_relative(1150, 600);
    pros::delay(500);
    intake.move(0);
    translate(0, 5, true, false, false, 0);

    //shoot 2 discs
    rotate(180 - 9, 0);
    pros::delay(950);
    shoot(2, 580);

    //set rpm for second volley
    setFlywheelRPM(473);


    pros::delay(200);

    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    //translatevl(43, 33, false, 9000, true, false, 46);
    translatevl(43, 33.7, false, 6500, true, false, 0);

    //move back a bit
    //translate(30, 26, true, false, false, 0);

    //second volley
    rotate(180 - 31.5, 0);
    pros::delay(250);
    angler1Piston.set_value(false);
    pros::delay(250);
    shoot(3, 400);
    angler1Piston.set_value(true);
}

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    leftStarter();

    //set rpm for third volley
    setFlywheelRPM(469);

    //intake discs for third volley
    intake.move(127);
    rtranslatevl(8.3, -7, false, 6000, false, false, 4);
    rtranslatevl(0, -25, false, 7000, false, false, 0);
    rtranslatevl(-13, 34, true, 10000, false, false, 0);

    intake.move(0);
    //third volley
    angler1Piston.set_value(false);
    rotate(180 - 27, 0);
    pros::delay(200);
    shoot(3, 500);
    angler1Piston.set_value(true);

}

void redRight() {
    //red right
    initAuton(greatapi::SRAD(PI));

    setFlywheelRPM(480);

    rtranslatevl(0, 5, true, 7000, false, false, 0);
    rotate(180 + 12, 0);
    pros::delay(1100);
    shoot(2, 550);
    angler1Piston.set_value(true);

    //intake discs for second volley
    intake.move(127);
    rtranslatevl(-38, 38, false, 8000, true, false, 0);

    rotate(180 + 44, 0);
    intake.move(0);

    //second volley
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 400);
    angler1Piston.set_value(true);
    translate(12, 5, false, true, false, 0);
    rtranslate(2, -10, false, true, false);
    pros::delay(500);
    intake.move_relative(1150, 600);
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
    leftStarter();
    setFlywheelRPM(480);
    
    intake.move(127);
    translatevl(100, 75, false, 10000, true, false, 2);
    intake.move(0);
    translatevl(108, 78, false, 10000, false, false, 0);

    rtranslate(10, 0, false, false, false);
    pros::delay(600);
    intake.move_relative(1150, 600);
    pros::delay(500);
    intake.move(0);

    //angler1Piston.set_value(false);
    rtranslatevl(-12, 0, true, 8000, false, false, 0);
    
    // rotate(90 - 11, 0);
    // shoot(3, 400);
    // angler1Piston.set_value(true);
}