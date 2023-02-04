#include "autons.hpp"
#include "pros/rtos.hpp"

void redLeft() {
    //red left
    //targetPos = redLStart;
    //location = redLStart;
    odomRotation.applyOffset(greatapi::SRAD(PI));
    setFlywheelRPM(500);
    intake.move(127);
    rtranslate(0, -30, false, true, false);
    pros::delay(650);
    intake.move(0);
    rtranslate(0, 34, true, false, false, 0);
    pros::delay(300);
    //rtranslate(0, -4, false, false, false, 0);
    rotate(180 - 5, 0);
    pros::delay(3500);
    shoot(2);
    setFlywheelRPM(485);
    //rtranslate(1, -1, false, false, false, 0);
    targetPos = location;
    //rotate(45, 0);
    intake.move(127);
    rtranslate(35, 24, false, 4000, true, false, 0);
    rotate(180 - 30, 0);
    pros::delay(1000);
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
    redLeft();
}

void blueRight() {
    //blue right
    red_team = false;
    redRight();
}

void skills() {
    //skills RED TEAM
    red_team = true;
    // //red left
    // //31.75, 9

    odomRotation.applyOffset(greatapi::SRAD(PI));
    setFlywheelRPM(385);
    intake.move(127);
    rtranslate(0, -2, false, true, false);
    pros::delay(300);
    intake.move(0);
    translate(5, 10, true, false, false, 0);
    intake.move(127);
    rtranslate(-25, 7, false, false, false, 0);
    pros::delay(300);
    angler1Piston.set_value(true);
    intake.move(0);
    rtranslate(5, 40, true, false, false, 0);
    fastShoot(3);
    //intake disks for second volley near blue low goal
    intake.move(127);
    rtranslate(20, 0, false, false, false, 0);
    rotate(180 - 55, 0);
    fastShoot(3);
    intake.move(127);
    rtranslate(-2, 25, false, false, false, 0);
    rotate(84, 0);
    fastShoot(3);






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