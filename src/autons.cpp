#include "autons.hpp"
#include "pros/rtos.hpp"

void leftStarter() {
    initAuton(greatapi::SRAD(0));

    setFlywheelRPM(485);

    pros::delay(100);
    //intake.move(127);

    //roller
    translate(0, -10, true, false, false);
    pros::delay(300);
    intake.move_relative(500, 600);
    pros::delay(400);
    intake.move(0);
    translate(0, 8, false, false, false, 0);

    //shoot 2 discs
    rotate(360 - 11, 0);
    pros::delay(1200);
    //fastShoot();
    shoot(2, 500);

    //set rpm for second volley
    setFlywheelRPM(473);


    pros::delay(200);

    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    //translatevl(43, 33, false, 9000, true, false, 46);
    translatevl(32, 36, true, 6500, true, true, 0);

    //move back a bit
    //translate(30, 26, true, false, false, 0);
    pros::delay(500);

    //second volley
    rotate(360 - 31.5, 0);
    pros::delay(200);
    angler1Piston.set_value(false);
    pros::delay(450);
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
    std::pair<double, double> path1[] = {std::make_pair(40, 36), std::make_pair(40, 12)};
    ptranslatevl(path1, 2, true, 6000, false, false, 0);

    // rtranslatevl(7.5, -3, true, 6000, false, false, 4);
    // rtranslatevl(0, -22, true, 7000, false, false, 0);
    // rtranslatevl(-13, 34, false, 10000, false, false, 0);

    // intake.move(0);
    // //third volley
    // angler1Piston.set_value(false);
    // rotate(360 - 27, 0);
    // pros::delay(200);
    // shoot(3, 500);
    // angler1Piston.set_value(true);

}

void redRight() {
    //red right
    initAuton(greatapi::SRAD(PI));
    angler1Piston.set_value(true);


    setFlywheelRPM(480);

    translatevl(0, 25, true, 8000, false, false, 0);
    pros::delay(300);
    rotate(360 - 17, 0);
    angler1Piston.set_value(false);
    pros::delay(200);
    shoot(3, 550);

    translate(6, 20, true, false, false, 2);
    translate(6, 3, true, false, false, 1.5);

    rtranslate(0, -10, true, false, false);
    pros::delay(300);
    intake.move_relative(250, 600);
    pros::delay(200);
    intake.move(0);
    rtranslate(0, 13, false, false, false, 0);

    angler1Piston.set_value(true);

    translate(5, 30, true, true, true, 0);


    //intake discs for second volley
    intake.move(127);
    rtranslatevl(-30, 30, true, 8000, false, false, 0);


    rotate(180 + 44, 0);

    //second volley
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 400);
    angler1Piston.set_value(true);

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