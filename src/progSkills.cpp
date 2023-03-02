#include "progSkills.hpp"

void skills() {

    //skills RED TEAM
    initAuton(greatapi::SRAD(PI));

    angler1Piston.set_value(true);

    //set flywheel rpm for first volley
    setFlywheelRPM(360);

    pros::delay(100);

    //first roller
    translate(0, -10, false, true, false);
    pros::delay(200);
    intake.move_relative(800, 600);
    pros::delay(350);
    intake.move(0);

    //move forward from roller
    translate(5, 19, true, false, false, 0);
    intake.move(127);
    //move to second roller
    translatevl(-22, 14, false, 7000, false, false, 0);
    intake.move(0);

    //second roller
    rtranslatevl(-10, 0, false, 7000, false, false);
    pros::delay(300);
    intake.move_relative(800, 600);
    pros::delay(350);
    intake.move(0);
    rtranslate(17, 0, true, false, false, 0);

    //move to first volley shoot spot
    intake.move(127);
    translatevl(-23.3, 73.6, true, 7000, false, false, 0);
    intake.move(0);

    //first volley
    rotate(180 + 4, 0);
    fastShoot(95, 1300);

    //set rpm for second volley
    setFlywheelRPM(377);

    //intake discs for second volley
    intake.move(127);
    rotate(108, 0);
    translatevl(13, 76, false, 4000, false, false, 0);
    pros::delay(700);
    intake.move(0);
    translatevl(19, 75.5, false, 5000, false, false, 0);
    
    //second volley
    rotate(180 - 47, 0);
    pros::delay(200);
    fastShoot(50, 900);
    fastShoot(127, 500);

    //set rpm for third volley
    setFlywheelRPM(376);
    
    //intake discs for third volley
    intake.move(127);
    rotate(0, 0);
    pros::delay(300);
    translatevl(18, 112, false, 7000, false, false, 0);
    //rtranslatevl(2, 5, false, 6000, false, false, 0);
    translate(18, 74, true, false, false, 0);

    //third volley
    rotate(180 - 43, 0);
    pros::delay(200);
    fastShoot(50, 900);
    fastShoot(127, 500);

    //set rpm for fourth volley
    setFlywheelRPM(440);

    //intake discs for fourth volley
    intake.move(127);
    translatevl(57, 105, false, 7000, true, false, 25);
    rtranslatevl(0, 0, false, 5000, false, false, 0);

    //fourth volley
    pros::delay(600);
    rotate(90 + 5, 0);
    angler1Piston.set_value(false);
    pros::delay(300);
    shoot(3, 500);
    angler1Piston.set_value(true);

    //move to third roller
    translate(64, 105, false, false, false, 2);
    translate(68, 115, false, false, false, 0);
    intake.move(0);

    //third roller
    rtranslatevl(0, 10, false, 7000, false, false);
    pros::delay(350);
    intake.move_relative(850, 600);
    pros::delay(400);
    intake.move(0);
    //move out from roller
    rtranslate(0, -10, true, false, false, 0);

    //set rpm for fifth volley
    setFlywheelRPM(365);

    //go to fourth roller and intake discs for fifth volley
    intake.move(127);
    translatevl(50, 90, true, 7000, false, false, 0);
    translatevl(85, 88.5, false, 4500, false, false, 0);
    intake.move(0);

    //fourth roller
    rtranslatevl(10, 0, false, 8000, false, false);
    pros::delay(200);
    intake.move_relative(900, 600);
    pros::delay(350);
    intake.move(0);

    //move out from roller
    rtranslatevl(-17, 0, true, 8000, false, false, 0);
    intake.move(127);

    //move to fifth volley shoot spot
    translate(83.2, 43.4, true, false, false, 0);

    //fifth volley
    rotate(9, 0);
    pros::delay(200);
    fastShoot(127, 1300);

    //set rpm for sixth volley
    setFlywheelRPM(381);

    //intake discs for sixth volley
    intake.move(127);
    rotate(290, 0);
    pros::delay(250);
    rtranslatevl(-35, 0.8, false, 5000, false, false, 0);
    pros::delay(700);
    intake.move(0);
    rtranslatevl(-7, 0.6, false, 5000, false, false, 0);

    //sixth volley
    rotate(360 - 46, 0);
    pros::delay(300);
    fastShoot(70, 800);
    fastShoot(127, 500);
    
    //set rpm for seventh volley
    setFlywheelRPM(385);

    //intake discs for seventh volley
    intake.move(127);
    rotate(180, 0);
    rtranslatevl(-1.25, -40, false, 7000, false, false, 0);
    rtranslate(-1, 40, true, false, false, 0);

    //seventh volley
    rotate(360 - 47, 0);

    pros::delay(250);
    fastShoot(70, 800);
    fastShoot(127, 500);

    //set rpm for eighth volley
    setFlywheelRPM(440);

    //intake discs for eighth volley
    intake.move(127);
    rtranslate(-38, -31, false, false, false, 25);
    rtranslatevl(0, 0, false, 6000, false, false, 0);

    //eighth volley
    rotate(277, 0);
    pros::delay(200);
    angler1Piston.set_value(false);
    pros::delay(200);
    shoot(3, 600);
    angler1Piston.set_value(true);

    //set rpm for ninth volley
    setFlywheelRPM(480);

    intake.move(127);
    rtranslatevl(-5, 20, false, 6000, true, false, 0);

    //ninth volley
    rotate(175, 0);
    pros::delay(300);
    angler1Piston.set_value(false);
    pros::delay(200);
    shoot(3, 600);
    translatevl(10, 10, false, 10000, true, false, 0);

    //expand
    intake.move(-127);
    angler1Piston.set_value(false);
    rotate(180 + 45, 0);
    // expansionPiston.set_value(true);


    pros::delay(500);
    moveDrive = false;

    // //rotate to expand
    // rotate(45, 0);
    // pros::delay(500);
    // //expand
    // expansionPiston.set_value(true);



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
    // translate(34, 58, 8000, false, false, 15);
    // fastShoot(1);

    // setFlywheelRPM(310);// prep for disc 17
    // translate(34, 58, 8000, false, false, 0);
    // fastShoot(1);

    // //get into pos for expansion
    // setFlywheelRPM(0);
    // intake.move(0);
    // alignGoal = 0;
    // rotate(-135);
    // translate(20, 26, false, false, 0);
    // expansionPiston.set_value(1);
}