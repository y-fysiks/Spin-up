#include "autons.hpp"
#include "pros/rtos.hpp"
#include <utility>

void leftStarter() {
    initAuton(greatapi::SRAD(0));

    //pros::delay(100);

    setFlywheelRPM(490);

    pros::delay(100);
    //intake.move(127);

    //roller
    translate(0, -10, true, false, false);
    pros::delay(300);
    intake.move_relative(500, 600);
    pros::delay(400);
    intake.move(0);
    translate(0, 8, false, false, false, 0);
    pros::delay(500);

    //shoot 2 discs
    rotate(360 - 9, 0);
    pros::delay(1300);
    //fastShoot();
    shoot(2, 400);

    //set rpm for second volley
    setFlywheelRPM(462);


    pros::delay(200);

    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    //translatevl(43, 33, false, 9000, true, false, 46);
    translatevl(34, 37, true, 4700, true, true, 0);

    //move back a bit
    //translate(30, 26, true, false, false, 0);
    pros::delay(250);

    //second volley
    rotate(360 - 32.5, 0);
    pros::delay(200);
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 350);
    angler1Piston.set_value(true);
}

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    leftStarter();

    //set rpm for third volley
    setFlywheelRPM(460);

    //intake discs for third volley
    intake.move(127);

    std::pair<double, double> path1[] = {std::make_pair(50, 44), std::make_pair(45, 10)};

    ptranslatevl(path1, 2, true, 7000, false, false, 0);

    translatevl(38, 38, false, 9000, false, false, 0);

    // intake.move(0);
    //third volley
    angler1Piston.set_value(false);
    rotate(360 - 27, 0);
    pros::delay(200);
    shoot(3, 400);
    angler1Piston.set_value(true);

}

void redRight() {
    //red right
    initAuton(greatapi::SRAD(PI));
    angler1Piston.set_value(true);

    setFlywheelRPM(480);
    pros::delay(50);

    intake.move(127);

    translatevl(18, 17.5, true, 6000, false, false, 0);
    pros::delay(500);

    //pull back
    translatevl(9, 12, false, 8000, false, false, 0);

    rotate(15, 0);

    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 500);

    angler1Piston.set_value(true);

    // translate(5, 30, true, true, true, 0);


    //intake discs for second volley
    intake.move(127);
    rtranslatevl(-33, 33, true, 8000, false, false, 0);
    rtranslatevl(4, 4, false, 6000, false, false, 0);


    rotate(43, 0);

    //second volley
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 350);
    angler1Piston.set_value(true);

    //move to roller
    intake.move(0);

    //std::pair<double, double> pathR[] = {std::make_pair(23,18), std::make_pair(14, 3)};

    //ptranslatevl(pathR, 2, true, 6000, true, true, 0);

    translatevl(16, 13, true, 6000, true, true, 2);
    translatevl(14, 2, true, 6000, false, false, 0);

    rtranslate(0, -10, true, false, false);
    pros::delay(400);
    intake.move_relative(250, 600);
    pros::delay(200);
    intake.move(0);
    rtranslate(0, 10, false, false, false, 0);

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