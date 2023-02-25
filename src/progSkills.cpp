#include "progSkills.hpp"

void skills() {

    //skills RED TEAM
    initAuton(greatapi::SRAD(PI));

    angler1Piston.set_value(true);

    //set flywheel rpm for first volley
    setFlywheelRPM(365);

    pros::delay(100);

    //first roller
    translate(0, -10, false, true, false);
    pros::delay(200);
    intake.move_relative(850, 600);
    pros::delay(350);
    intake.move(0);
//67.5 112.75
    //move forward from roller
    translate(5, 19, true, false, false, 0);
    intake.move(127);
    //move to second roller
    translatevl(-22, 15, false, 8000, false, false, 0);
    intake.move(0);

    //second roller
    rtranslatevl(-10, 0, false, 8000, false, false);
    pros::delay(250);
    intake.move_relative(900, 600);
    pros::delay(380);
    intake.move(0);
    rtranslate(17, 0, true, false, false, 0);

    //move to first volley shoot spot
    intake.move(127);
    translatevl(-23, 74, true, 7000, false, false, 0);
    intake.move(0);
    rotate(180 + 6, 0);
    fastShoot();

    //set rpm for second volley
    setFlywheelRPM(385);

    //intake discs for second volley
    intake.move(127);
    rotate(96, 0);
    translatevl(17.2, 75, false, 6000, false, false, 0);
    
    //second volley
    rotate(180 - 45, 0);
    pros::delay(300);
    fastShoot();

    //set rpm for third volley
    setFlywheelRPM(365);
    
    //intake discs for third volley
    intake.move(127);
    rotate(0, 0);
    pros::delay(250);
    translatevl(17.6, 112, false, 7000, false, false, 0);
    rtranslatevl(2, 5, false, 6000, false, false, 0);


    //third volley
    rotate(84, 0);
    pros::delay(250);
    fastShoot();

    //set rpm for fourth volley
    setFlywheelRPM(420);

    //intake discs for fourth volley
    intake.move(127);
    translatevl(48, 87, false, 8000, false, false, 30);
    rtranslatevl(0, 0, false, 5000, true, false, 0);

    //fourth volley
    rotate(90 + 32, 0);
    shoot(3, 500);

    //move to third roller
    translate(65, 105, false, true, false, 2);
    translate(67, 111.5, false, false, false, 0);

    //third roller
    rtranslatevl(0, 10, false, 8000, false, false);
    pros::delay(250);
    intake.move_relative(900, 600);
    pros::delay(350);
    intake.move(0);
    //move out from roller
    rtranslatevl(0, -10, true, 10000, false, false, 0);

    //set rpm for fifth volley
    setFlywheelRPM(365);

    //go to fourth roller and intake discs for fifth volley
    intake.move(127);
    translate(58, 75, true, false, false, 0);
    translatevl(100, 80, false, 8000, false, false, 0);
    intake.move(0);

    //fourth roller
    rtranslatevl(10, 0, false, 10000, false, false, 0);
    pros::delay(200);
    intake.move_relative(900, 600);
    pros::delay(350);
    intake.move(0);

    //move out from roller
    rtranslatevl(-17, 0, true, 10000, false, false, 0);
    intake.move(127);

    // //move to fifth volley shoot spot
    // translate(100, 40, true, false, false, 0);

    // //fifth volley
    // rotate(6, 0);
    // fastShoot();

    // //set rpm for sixth volley
    // setFlywheelRPM(385);

    // //intake discs for sixth volley
    // intake.move(127);
    // rotate(270, 0);
    // rtranslatevl(-40, 0, false, 8000, false, false, 0);
    
    // //sixth volley
    // rotate(360 - 45, 0);
    // pros::delay(300);
    // fastShoot();
    
    // //set rpm for seventh volley
    // setFlywheelRPM(365);

    // //intake discs for seventh volley
    // intake.move(127);
    // rotate(180, 0);
    // rtranslatevl(0,-40, false, 8000, false, false, 6);
    // rtranslatevl(7, 0, false, 6000, false, false, 0);

    // //seventh volley
    // rotate(180 + 84, 0);
    // pros::delay(250);
    // fastShoot();

    // //set rpm for eighth volley
    // setFlywheelRPM(400);

    // //intake discs for eighth volley
    // intake.move(127);
    // rtranslate(-40, 35, false, false, false, 25);
    // rtranslatevl(0, 0, false, 6000, false, false, 0);

    // //eighth volley
    // rotate(180 + 90 + 32, 0);
    // pros::delay(300);
    // shoot(3, 500);

    // //set rpm for ninth volley
    // setFlywheelRPM(430);

    // //intake discs for ninth volley
    // intake.move(127);
    // rtranslatevl(-18, -25, false, 7000, false, false, 0);

    // //ninth volley
    // rotate(280, 0);
    // pros::delay(300);
    // shoot(3, 650);

    // //expand
    // intake.move(-127);
    // angler1Piston.set_value(false);
    // rotate(180 + 45, 0);
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