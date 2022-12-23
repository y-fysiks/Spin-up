#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    red_team = true;
    //31.75, 9
    rtranslate(0, -2, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(372);
    pros::delay(3000);
    rtranslate(4, 12, false, false, 0);
    rotate(-15, 0);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(362);
    pros::delay(2000);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(200);
}

void redRight() {
    //red right
    red_team = true;
    rtranslate(-2, 0, false, false, 0);
    rtranslate(0, 23.4, false, false, 0);
    rtranslate(2, 0, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(362);
    pros::delay(2000);
    rtranslate(-12, -4, false, false, 0);
    rotate(270 + 18, 0);
    pros::delay(500);
    shoot(1);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(200);

}

void blueLeft() {
    //blue left
    red_team = false;
    rtranslate(0, 2, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(362);
    pros::delay(2000);
    rtranslate(-4, -12, false, false, 0);
    rotate(180 - 18, 0);
    pros::delay(500);
    shoot(1);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(200);
}

void blueRight() {
    //blue right
    red_team = false;
    rtranslate(2, 0, false, false, 0);
    rtranslate(0, -23.4, false, false, 0);
    rtranslate(-2, 0, false, false);
    pros::delay(500);
    roller.move_relative(-90, 100);
    setFlywheelRPM(362);
    pros::delay(2000);
    rtranslate(12, 4, false, false, 0);
    rotate(90 + 18, 0);
    pros::delay(500);
    shoot(1);
    pros::delay(500);
    shoot(1);
    setFlywheelRPM(200);
}

void skills() {
    //skills RED TEAM
    red_team = true;
    //red left
    //31.75, 9
    rtranslate(0, -2, false, false);
    pros::delay(500);
    roller.move_relative(-190, 100);
    pros::delay(700);
    rtranslate(4, 12, false, false, 0);

    setFlywheelRPM(200);
    intake.move(-127);
    translate(20, 28, false, false, 0);
    rotate(90, 0);
    translate(12, 28, false, false, 0.5);
    rtranslate(-2, 0, false, false);
    pros::delay(500);
    roller.move_relative(-190, 100);
    pros::delay(700);
    setFlywheelRPM(380);//prep for discs 1-3

    translate(25, 25, false, false, 0);

    rotate(92, 0);
    shoot(3);
    rotate(180 - 45);
    translate(70.2, 74.2, 5000, false, false, 47);//134.35 total distance
    
    setFlywheelRPM(300);// prep for disc 4
    translate(70.2, 74.2, 5000, false, false, 20);
    alignGoal = 2;
    pros::delay(500);
    fastShoot(1);

    setFlywheelRPM(300);// prep for disc 5
    translate(70.2, 74.2, 5000, false, false, 0);
    fastShoot(1);

    setFlywheelRPM(300);// prep for disc 6
    translate(106, 112, 5000, false, false, 32);
    fastShoot(1);

    setFlywheelRPM(320);// prep for disc 7
    translate(106, 112, 5000, false, false, 18);
    fastShoot(1);

    setFlywheelRPM(330);// prep for disc 8-10
    translate(106, 112, 5000, false, false, 0);
    shoot(3);
    alignGoal = 0;


    rotate(180, 0);
    translate(115, 121, false, false, 0);

    //rollers
    rtranslate(0, 2, false, false);
    pros::delay(500);
    roller.move_relative(-190, 100);
    pros::delay(700);
    rtranslate(0, -5, false, false, 0);
    rotate(270, 0);

    setFlywheelRPM(340);// prep for disc 11
    translate(128, 103, false, false, 0);
    rtranslate(2, 0, false, false);
    pros::delay(500);
    roller.move_relative(-190, 100);
    pros::delay(700);
    //move out from roller and rotate to shoot disc
    rtranslate(-20, 0, false, false, 0);
    rotate(45, 0);
    expansionPiston.set_value(true);
    // alignGoal = 2;
    // fastShoot(1);
    // alignGoal = 0;

    // setFlywheelRPM(290);// prep for disc 12-14
    // rotate(-45);
    // translate(89, 58, false, false, 0);
    // rotate(130, 0);
    // fastShoot(3);
    // rotate(45);
    // translate(58, 90, false, false, 0);
    // rotate(-45, 0);
    // fastShoot(1);// shoot disc 15

    // setFlywheelRPM(300);// prep for disc 16
    // alignGoal = 1;
    // translate(34, 58, 10000, false, false, 15);
    // fastShoot(1);

    // setFlywheelRPM(310);// prep for disc 17
    // translate(34, 58, 10000, false, false, 0);
    // fastShoot(1);

    // //get into pos for expansion
    // setFlywheelRPM(0);
    // intake.move(0);
    // alignGoal = 0;
    // rotate(-135);
    // translate(20, 26, false, false, 0);
    // expansionPiston.set_value(1);
}