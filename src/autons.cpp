#include "autons.hpp"
#include "pros/rtos.hpp"
#include <utility>

void leftStarter8Disk() {
    initAuton(greatapi::SRAD(0));

    setFlywheelRPM(550);

    //roller
    translate(0, -10, true, false, false);
    pros::delay(300);
    intake.move_relative(500, 600);
    pros::delay(400);
    intake.move(0);
    translate(0, 9, false, false, false, 0);
    //pros::delay(500);

    //shoot 2 discs
    rotate(360 - 11.3, 0);
    pros::delay(2500);
    //fastShoot();
    shoot(2, 475);

    //set rpm for second volley
    setFlywheelRPM(522);


    //pros::delay(100);

    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    //translatevl(43, 33, false, 9000, true, false, 46);
    translatevl(34, 37, true, 7000, true, true, 0);

    //move back a bit
    //translate(30, 26, true, false, false, 0);
    //pros::delay(250);

    //second volley
    rotate(360 - 37.2, 0);
    //pros::delay(200);
    angler1Piston.set_value(false);
    pros::delay(350);
    shoot(3, 428);
    angler1Piston.set_value(true);
}

void leftStarter9Disk() {
    initAuton(greatapi::SRAD(0));

    setFlywheelRPM(508);
    angler1Piston.set_value(true);

    //roller
    translate(0, -10, true, false, false);
    pros::delay(300);
    intake.move_relative(500, 600);
    pros::delay(400);
    intake.move(0);
    translate(0, 5, false, false, false, 0);
    intake.move(127);
    translatevl(-8, 11, true, 8000, true, true, 0);
    translate(2, 8, false, false, false, 0);


    //pros::delay(500);

    //shoot 2 discs
    rotate(360 - 14, 0);
    angler1Piston.set_value(false);
    pros::delay(350);
    //fastShoot();
    shoot(3, 400);

    //set rpm for second volley
    setFlywheelRPM(469);


    //pros::delay(100);

    
    //intake discs for second volley
    angler1Piston.set_value(true);
    intake.move(127);
    //translatevl(43, 33, false, 9000, true, false, 46);
    translatevl(34, 38, true, 8000, true, true, 0);

    //move back a bit
    //translate(30, 26, true, false, false, 0);
    pros::delay(150);

    //second volley
    rotate(360 - 39.5, 0);
    pros::delay(200);
    angler1Piston.set_value(false);
    pros::delay(350);
    shoot(3, 275);
    angler1Piston.set_value(true);
}

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    leftStarter8Disk();

    //set rpm for third volley
    //setFlywheelRPM(484);

    //intake discs for third volley
    intake.move(127);

    std::pair<double, double> path1[] = {std::make_pair(44.25, 35), std::make_pair(44.5, 5)};

    ptranslatevl(path1, 2, true, 7000, true, true, 0);

    translatevl(38, 38, false, 12000, false, false, 2);

    // intake.move(0);
    //third volley
    angler1Piston.set_value(false);
    rotate(360 - 39.9, 0);
    pros::delay(350);
    shoot(3, 425);
    angler1Piston.set_value(true);

}

void redRight() {
    //red right
    initAuton(greatapi::SRAD(PI));

    pros::delay(50);

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
    leftStarter8Disk();

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