#include "progSkills.hpp"

void skills() {

    //skills RED TEAM
    initAuton(greatapi::SRAD(0));

    angler1Piston.set_value(true);

    //set flywheel rpm for first volley
    setFlywheelRPM(360);

    pros::delay(100);

    //first roller
    translate(0, -10, true, true, true);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(350);
    intake.move(0);

    //move forward from roller
    translate(5, 19, false, false, false, 0);
    intake.move(127);
    //move to second roller
    translatevl(-22, 14, true, 7000, false, false, 0);
    intake.move(0);

    //second roller
    rtranslatevl(-10, 0, true, 7000, false, false);
    pros::delay(400);
    intake.move_relative(750, 600);
    pros::delay(400);
    intake.move(0);
    rtranslate(17, 0, false, false, false, 0);

    //move to first volley shoot spot
    intake.move(127);
    translatevl(-20.8, 71, false, 8000, false, false, 0);
    intake.move(0);

    //first volley
    pros::delay(200);
    rotate(7, 0);
    fastShoot();

    //set rpm for second volley
    setFlywheelRPM(374);

    //intake discs for second volley
    intake.move(127);
    rotate(180 + 110, 0);
    pros::delay(200);
    translatevl(3, 74.1, true, 6000, false, false, 2);
    translatevl(12, 74.1, true, 6000, false, false, 2);
    pros::delay(1700);
    intake.move(0);
    translatevl(22.2, 74.1, true, 7000, false, false, 0);
    
    //second volley
    rotate(360 - 50, 0);
    pros::delay(200);
    fastShoot();

    //set rpm for third volley
    setFlywheelRPM(374);
    
    //intake discs for third volley
    intake.move(127);
    rotate(180, 0);
    pros::delay(300);
    translatevl(20, 112, true, 4000, false, false, 0);
    //rtranslatevl(2, 5, false, 6000, false, false, 0);
    translatevl(20, 74, false, 6000, false, false, 0);

    //third volley
    rotate(360 - 43, 0);
    pros::delay(200);
    fastShoot();

    //set rpm for fourth volley
    setFlywheelRPM(444);

    //intake discs for fourth volley
    intake.move(127);
    translatevl(57, 103, true, 5000, true, true, 25);
    rtranslatevl(0, 0, true, 5000, false, false, 0);

    //fourth volley
    pros::delay(600);
    rotate(270 + 9, 0);
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 500);
    angler1Piston.set_value(true);

    //move to third roller
    translate(64, 105, true, false, false, 2);
    translate(68, 111, true, false, false, 0);
    intake.move(0);

    //third roller
    rtranslatevl(0, 10, true, 7000, false, false);
    pros::delay(500);
    intake.move_relative(800, 600);
    pros::delay(400);
    intake.move(0);
    location.y = 118;
    //move out from roller
    rtranslate(0, -10, false, false, false, 0);

    //set rpm for fifth volley
    setFlywheelRPM(362);

    //go to fourth roller and intake discs for fifth volley
    intake.move(127);
    translatevl(50, 90, false, 7000, false, false, 0);
    translatevl(90, 88.5, true, 4000, false, false, 0);
    intake.move(0);

    //fourth roller
    rtranslatevl(10, 0, true, 8000, false, false);
    pros::delay(500);
    intake.move_relative(850, 600);
    pros::delay(350);
    intake.move(0);
    location.x = 94.5;

    //move out from roller
    rtranslatevl(-17, 0, false, 8000, false, false, 0);
    intake.move(127);

    //move to fifth volley shoot spot
    translate(84, 44.5, !true, false, false, 0);
    pros::delay(200);

    //fifth volley
    rotate(180 + 10.5, 0);
    pros::delay(200);
    fastShoot();

    //set rpm for sixth volley
    setFlywheelRPM(377);

    //intake discs for sixth volley
    intake.move(127);
    rotate(180 + 290, 0);
    pros::delay(250);
    rtranslatevl(-33, -0.5, !false, 5000, false, false, 0);
    pros::delay(1200);
    intake.move(0);
    rtranslatevl(-11, 0.7, !false, 10000, false, false, 0);

    //sixth volley
    rotate(180 - 42, 0);
    pros::delay(300);
    fastShoot();
    
    //set rpm for seventh volley
    setFlywheelRPM(378);

    //intake discs for seventh volley
    intake.move(127);
    rotate(180 + 190, 0);
    pros::delay(250);
    rtranslatevl(0.5, -40, !false, 7000, false, false, 0);
    rtranslate(0, 40, !true, false, false, 0);

    //seventh volley
    rotate(180 - 41, 0);

    pros::delay(250);
    fastShoot();

    //set rpm for eighth volley
    setFlywheelRPM(443);

    //intake discs for eighth volley
    intake.move(127);
    rtranslate(-38, -31, !false, false, false, 25);
    rtranslatevl(0, 0, !false, 6000, false, false, 0);

    //eighth volley
    rotate(180 + 277, 0);
    pros::delay(400);
    angler1Piston.set_value(false);
    pros::delay(400);
    shoot(3, 300);
    angler1Piston.set_value(true);

    //set rpm for ninth volley
    //setFlywheelRPM(480);

    intake.move(-127);
    //rtranslatevl(-5, 20, false, 6000, true, false, 0);

    //ninth volley
    // rotate(175, 0);
    // pros::delay(300);
    // angler1Piston.set_value(false);
    // pros::delay(200);
    // shoot(3, 600); 
    translatevl(-16, 20, !false, 10000, true, !false, 0);

    //expand
    intake.move(-127);
    angler1Piston.set_value(false);
    rotate(45, 0);
    expansionPiston.set_value(true);

}