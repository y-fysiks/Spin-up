#include "autons.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    initAuton(greatapi::SRAD(PI));

    setFlywheelRPM(494);
    //intake.move(127);
    pros::delay(100);
    translate(0, -12.5, false, false, false);
    pros::delay(200);
    intake.move_relative(1200, 600);
    pros::delay(503);
    intake.move(0);
    translate(0, 5, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 9, 0);
    pros::delay(500);
    shoot(2);
    setFlywheelRPM(473);
    //rtranslate(1, -1, false, false, false, 0);
    targetPos = location;
    //rotate(45, 0);
    angler1Piston.set_value(true);
    intake.move(127);
    translate(40, 30, false, 12000, true, false, 18);
    translate(40, 30, false, 5000, false, false, 0);

    rotate(180 - 27, 0);
    angler1Piston.set_value(false);
    pros::delay(1000);
    shoot(3);
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
    redLeft();
    
    intake.move(127);
    translate(107, 76, false, 8000, true, false, 20);
    intake.move(0);
    translate(107, 76, false, false, false, 0);
    translate(115, 68, false, 0, false);

    //rtranslate(3, 0, false, true, false);
    pros::delay(500);
    intake.move_relative(1200, 600);
    pros::delay(500);
    intake.move(0);
}

void skills() {
    /*
    roller 2
    -22, 15
    shooter
    -20, 75
    rotate 90
    22, 75
    rotate 135
    shoot x3
    rotate 0
    25, 118
    rotate -95
    shoot x3
    x + 29 y -27
    
    */

    //skills RED TEAM
    red_team = true;
    // //red left
    // //31.75, 9
    initAuton(greatapi::SRAD(PI));

    angler1Piston.set_value(true);

    setFlywheelRPM(390);
    pros::delay(100);

    //first roller
    translate(0, -10, false, 10000, true, false);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(300);
    intake.move(0);

    //move forward from roller
    translate(5, 18, true, 8000, false, false, 0);
    intake.move(127);
    //move to second roller
    translate(-23, 15, false, 6000, false, false, 0);
    intake.move(0);

    //second roller
    rtranslate(-10, 0, false, 8000, false, false);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(300);
    intake.move(0);
    rtranslate(18, 0, true, 10000, false, false, 0);

    //move to first volley shoot spot
    intake.move(127);
    translate(-24, 74.5, true, 7000, false, false, 0);
    intake.move(0);
    rotate(180 + 3, 0);
    fastShoot();

    //intake discs for second volley
    intake.move(127);
    setFlywheelRPM(400);
    rotate(90, 0);
    translate(17, 75, false, 6000, false, false, 0);
    //second volley
    rotate(180 - 46, 0);
    fastShoot();
    
    //intake discs for third volley
    intake.move(127);
    setFlywheelRPM(390);
    translate(16, 117, false, 10000, true, false, 0);
    intake.move(0);

    //third volley
    rotate(87, 0);
    fastShoot();

    //intake discs for fourth volley
    intake.move(127);
    translate(60, 87, false, 10000, true, false, 20);
    translate(54, 87, false, 10000, false, false, 0);
    translate(80, 87, false, 10000, true, false, 0);

    //third roller
    rtranslate(2, 0, false, 8000, false, false);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(300);
    intake.move(0);
    //move out from roller
    rtranslate(-8, 0, true, 10000, false, false, 0);

    //fourth volley
    rotate(3, 0);
    shoot(3);

    //go to fourth roller
    intake.move(127);
    rtranslate(0, 30, false, 8000, false, false, 0);

    //fourth roller
    rtranslate(0, 5, false, 10000, false, false, 0);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(300);
    intake.move(0);

    //move out from roller
    rtranslate(0, -8, true, 10000, false, false, 0);

    //rotate to expand
    rotate(45, 0);
    pros::delay(500);
    //expand
    expansionPiston.set_value(true);



    // rotate(-60, 0);
    

    // pros::delay(300);



    // angler1Piston.set_value(true);
    // intake.move(0);
    // rtranslate(5, 40, true, false, false, 0);
    // fastShoot(3);
    // //intake disks for second volley near blue low goal
    // intake.move(127);
    // rtranslate(20, 0, false, false, false, 0);
    // rotate(180 - 55, 0);
    // fastShoot(3);
    // intake.move(127);
    // rtranslate(-2, 25, false, false, false, 0);
    // rotate(84, 0);
    // fastShoot(3);






    // rtranslate(0, -2, false, false);
    // pros::delay(500);
    // roller.move_relative(-190, 100);
    // pros::delay(700);
    // rtranslate(4, 12, false, false, 0);

    // setFlywheelRPM(200);
    // intake.move(-127);
    // translate(20, 28, false, false, 0);
    // rotate(90, 0);
    // translate(12, 28, false, false, 0.5);
    // rtranslate(-2, 0, false, false);
    // pros::delay(500);
    // roller.move_relative(-190, 100);
    // pros::delay(700);
    // setFlywheelRPM(400);//prep for discs 1-3

    // translate(25, 25, false, false, 0);

    // rotate(92, 0);
    // shoot(3);
    // rotate(180 - 45);
    // translate(70.2, 74.2, 5000, false, false, 47);//134.35 total distance
    
    // setFlywheelRPM(310);// prep for disc 4
    // translate(70.2, 74.2, 6000, false, false, 20);
    // alignGoal = 2;
    // pros::delay(500);
    // fastShoot(1);

    // setFlywheelRPM(300);// prep for disc 5
    // translate(70.2, 74.2, 6000, false, false, 0);
    // fastShoot(1);

    // setFlywheelRPM(315);// prep for disc 6
    // translate(106, 112, 6000, false, false, 32);
    // fastShoot(1);

    // setFlywheelRPM(330);// prep for disc 7
    // translate(106, 112, 6000, false, false, 18);
    // fastShoot(1);

    // setFlywheelRPM(350);// prep for disc 8-10
    // translate(106, 112, 5000, false, false, 0);
    // shoot(3);

    // translate(120, 124, 6000, false, false, 0);
    // alignGoal = 0;

    // rotate(180, 0);
    // translate(112, 126, false, false, 0);

    // //rollers
    // rtranslate(0, 2, false, false);
    // pros::delay(500);
    // roller.move_relative(-190, 100);
    // pros::delay(700);
    // rtranslate(0, -2, false, false, 0);
    // rotate(270);

    // setFlywheelRPM(340);// prep for disc 11
    // translate(122, 110, false, false, 0);
    // rtranslate(2, 0, false, false);
    // pros::delay(500);
    // roller.move_relative(-190, 100);
    // pros::delay(700);
    // //move out from roller and rotate to shoot disc
    // rtranslate(-4, 0, false, false, 0);
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