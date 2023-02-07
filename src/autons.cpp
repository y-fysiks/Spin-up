#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    odomRotation.applyOffset(greatapi::SRAD(PI));


    setFlywheelRPM(492);
    //intake.move(127);
    rtranslate(0, -30, false, true, false);
    pros::delay(200);
    intake.move_relative(1200, 600);
    pros::delay(503);
    intake.move(0);
    rtranslate(1, 34, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 7, 0);
    pros::delay(2500);
    shoot(2);
    setFlywheelRPM(473);
    //rtranslate(1, -1, false, false, false, 0);
    targetPos = location;
    //rotate(45, 0);
    angler1Piston.set_value(true);
    intake.move(127);
    translate(40, 26, false, 12000, true, false, 20);
    translate(40, 26, false, 4000, false, false, 0);
    rotate(180 - 28.2, 0);
    angler1Piston.set_value(false);
    pros::delay(1500);
    shoot(3);
}

void redRight() {
    //red right
    odomRotation.applyOffset(greatapi::SRAD(PI));

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



    // rtranslate(-2, 0, false, false, false, 0);
    // rtranslate(0, 23.4, false, false, false, 0);
    // rtranslate(2, 0, false, false, false);
    // pros::delay(500);
    // intake.move_relative(-90, 100);
    // setFlywheelRPM(362);
    // pros::delay(2000);
    // rtranslate(-12, -4, false, false, 0);
    // rotate(270 + 18, 0);
    // pros::delay(500);
    // shoot(1);
    // pros::delay(500);
    // shoot(1);
    // setFlywheelRPM(200);

}

void blueLeft() {
    //blue left
    odomRotation.applyOffset(greatapi::SRAD(PI));
    setFlywheelRPM(492);
    //intake.move(127);
    rtranslate(0, -30, false, true, false);
    pros::delay(200);
    intake.move_relative(1200, 600);
    pros::delay(503);
    intake.move(0);
    rtranslate(1, 34, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 6.5, 0);
    pros::delay(2000);
    shoot(2);
    setFlywheelRPM(475);
    setFlywheelRPM(475);
    //rtranslate(1, -1, false, false, false, 0);
    targetPos = location;
    //rotate(45, 0);
    angler1Piston.set_value(true);
    intake.move(127);
    translate(40, 26, false, 12000, true, false, 20);
    translate(40, 26, false, 4000, true, false, 0);
    rotate(180 - 32.7, 0);
    angler1Piston.set_value(false);
    pros::delay(750);
    intake.move(-127);
    pros::delay(900);
    
    intake.move(127);
    translate(120, 70, false, true, false, 0);
    rtranslate(3, 0, false, true, false);
    pros::delay(500);
    intake.move_relative(1200, 600);
    pros::delay(500);
    intake.move(0);
    rtranslate(-5, 0, true, false, false, 0);
}

void blueRight() {
    //blue right
    red_team = false;
    redRight();

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

        odomRotation.applyOffset(greatapi::SRAD(PI));
    setFlywheelRPM(490);
    //intake.move(127);
    rtranslate(0, -30, false, true, false);
    pros::delay(200);
    intake.move_relative(1200, 600);
    pros::delay(503);
    intake.move(0);
    rtranslate(1, 34, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 6.5, 0);
    pros::delay(2500);
    shoot(2);
    setFlywheelRPM(475);
    //rtranslate(1, -1, false, false, false, 0);
    targetPos = location;
    //rotate(45, 0);
    angler1Piston.set_value(true);
    intake.move(127);
    translate(40, 26, false, 12000, true, false, 20);
    translate(40, 26, false, 4000, false, false, 0);
    rotate(180 - 27, 0);
    angler1Piston.set_value(false);
    pros::delay(1000);
    shoot(3);
    rtranslate(-20, -20, true, true, true, 0);
    expansionPiston.set_value(true);


    // angler1Piston.set_value(true);

    // odomRotation.applyOffset(greatapi::SRAD(PI));
    // setFlywheelRPM(390);
    // //intake.move(127);
    // rtranslate(0, -30, false, true, false);
    // pros::delay(200);
    // intake.move_relative(1200, 600);
    // pros::delay(503);
    // intake.move(0);

    // translate(5, 10, true, false, false, 0);
    // intake.move(127);
    // translate(-22, 17, false, false, false, 0);

    // //second roller
    // rtranslate(-30, 0, false, false, false);
    // pros::delay(200);
    // intake.move_relative(1200, 600);
    // pros::delay(503);
    // intake.move(0);
    // rtranslate(34, 0, true, false, false, 0);
    // //move to first volley shoot spot
    // translate(-20, 75, true, false, false, 0);
    // fastShoot(3);
    // intake.move(127);
    // setFlywheelRPM(400);
    // translate(22, 75, false, true, false, 0);
    // rotate(135, 0);
    // intake.move(0);
    // fastShoot(3);
    // intake.move(127);
    // setFlywheelRPM(390);
    // translate(25, 118, false, true, false, 0);
    // rotate(-95, 0);
    // intake.move(0);
    // fastShoot(3);
    // intake.move(127);
    // translate(54, 91, false, true, false, 20);
    // translate(54, 91, false, true, false, 0);



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