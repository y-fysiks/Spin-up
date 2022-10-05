#include "main.h"
#include "globals.hpp"

// this is the target position for the robot to try to reach
inline greatapi::position targetPos(greatapi::coord(0, 0), greatapi::SRAD(0));

/**
 * @brief odometry function
 * 
 */
void odometryLooper() {
    pros::screen::set_pen(COLOR_RED);
    right_encoder -> reset();
    left_encoder -> reset();
    rear_encoder -> reset();
    while (true) {
        location = odom.calculateposition(location);
        pros::screen::print(TEXT_SMALL, 1, "X: %.2f   Y: %.2f", location.x, location.y); //print X, Y and angle after each compute
        pros::screen::print(TEXT_SMALL, 2, "Angle: %.2f", location.angle / PI * 180);
        pros::delay(5);
    }
    return;
}

/**
 * @brief function to be run in a task to move the robot the the target position
 * 
 */
void position_control() {
    std::vector<greatapi::controlelement *> PIDXElements;
    //TODO TUNE PID FOR X
    greatapi::controlelement *PX = new greatapi::Proportional(2800, std::pair(__INT_MAX__, -__INT_MAX__));          PIDXElements.push_back(PX);
    greatapi::controlelement *IX = new greatapi::Integral(0, std::pair(__INT_MAX__, -__INT_MAX__));                 PIDXElements.push_back(IX);
    greatapi::controlelement *DX = new greatapi::Derivative(800, std::pair(__INT_MAX__, -__INT_MAX__));             PIDXElements.push_back(DX);

    greatapi::control_loop PIDX(PIDXElements, std::pair(12000, -12000));


    std::vector<greatapi::controlelement *> PIDYElements;
    //TODO TUNE PID FOR Y
    greatapi::controlelement *PY = new greatapi::Proportional(2800, std::pair(__INT_MAX__, -__INT_MAX__));          PIDYElements.push_back(PY);
    greatapi::controlelement *IY = new greatapi::Integral(0, std::pair(__INT_MAX__, -__INT_MAX__));                 PIDYElements.push_back(IY);
    greatapi::controlelement *DY = new greatapi::Derivative(1000, std::pair(__INT_MAX__, -__INT_MAX__));            PIDYElements.push_back(DY);

    greatapi::control_loop PIDY(PIDYElements, std::pair(12000, -12000));


    std::vector<greatapi::controlelement *> PIDAngleElements;
    //TODO TUNE PID FOR ANGLE
    greatapi::controlelement *PAngle = new greatapi::Proportional(20000, std::pair(__INT_MAX__, -__INT_MAX__));     PIDAngleElements.push_back(PAngle);
    greatapi::controlelement *IAngle = new greatapi::Integral(0, std::pair(__INT_MAX__, -__INT_MAX__));             PIDAngleElements.push_back(IAngle);
    greatapi::controlelement *DAngle = new greatapi::Derivative(10000, std::pair(__INT_MAX__, -__INT_MAX__));       PIDAngleElements.push_back(DAngle);

    greatapi::control_loop PIDAngle(PIDAngleElements, std::pair(12000, -12000));
    
    while (true) {
        //current position is location variable
        //target position is targetPos variable
        total_error = sqrt(pow(targetPos.x - location.x, 2) + pow(targetPos.y - location.y, 2));

        greatapi::coord error(location, targetPos);
        pros::screen::print(TEXT_SMALL, 3, "X error: %.2f  Y error: %.2f", error.x, error.y);
        error.self_transform_matrix(greatapi::SRAD(-1.0 * location.angle));

        double xMove = PIDX.update(error.x, 0);
        double yMove = PIDY.update(error.y, 0);
        double anglePow = PIDAngle.update(greatapi::findDiff(location.angle, targetPos.angle), 0);

        if (yMove > voltageCap) {
            yMove = voltageCap;
        } else if (yMove < -voltageCap) {
            yMove = -voltageCap;
        }
        

        double lfPower = yMove + xMove - anglePow;
        double rfPower = yMove - xMove + anglePow;
        double lbPower = yMove - xMove - anglePow;
        double rbPower = yMove + xMove + anglePow;

        if (moveDrive) {
            lf_motor.move_voltage(lfPower);
            rf_motor.move_voltage(rfPower);
            lb_motor.move_voltage(lbPower);
            rb_motor.move_voltage(rbPower);
        } else {
            
        }
        
        pros::screen::print(TEXT_SMALL, 4, "Angle power: %.2f", anglePow);
        pros::screen::print(TEXT_SMALL, 5, "Total error: %.2f", total_error);

        pros::delay(5);
    }
    return;
}

/**
 * @brief rotates the bot to the specified absolute heading. DOES NOT BLOCK EXECUTION
 * 
 * @param angle the absolute heading to rotate to
 */
void rotate(double angleDeg) {
    greatapi::SRAD angle = greatapi::SRAD((-1.0 * angleDeg) * PI / 180.0);
    targetPos.angle = angle;
    return;
}

/**
 * @brief rotates the bot to the specified absolute heading. Blocks execution until the bot is at the specified heading.
 * 
 * @param angle the absolute heading to rotate to
 * @param errorStop DEGREES the function will stop the bot if the error is greater than the error threshold. IF 0, default is 2 degrees
 */
void rotate(double angleDeg, double errorStop) {
    rotate(angleDeg);
    errorStop = errorStop == 0 ? 5 : errorStop;
    while (fabs(greatapi::findDiff(location.angle, targetPos.angle)) > greatapi::degrees(errorStop)) {
        pros::delay(50);
    }
    return;
}

/**
 * @brief translates the robot to absolute coordinates. DOES NOT BLOCK EXECUTION
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void translate(double x, double y, bool goHeading, bool reverseHeading) {
    if (goHeading) {
        if (reverseHeading) {
            rotate(90 - (atan2(y - location.y, x - location.x) + PI) / PI * 180.0, 0);
        } else {
            rotate(90 - (atan2(y - location.y, x - location.x)) / PI * 180.0, 0);
        }
    }
    targetPos.x = x;
    targetPos.y = y;
    total_error = sqrt(pow(targetPos.x - location.x, 2) + pow(targetPos.y - location.y, 2));
    return;
}

/**
 * @brief translates the robot to absolute coordinates. Blocks execution. 
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target
 * @param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.3
 */
void translate(double x, double y, bool goHeading, bool reverseHeading, double distToStopBlock) {
    translate(x, y, goHeading, reverseHeading);
    distToStopBlock = distToStopBlock == 0 ? 0.8 : distToStopBlock;
    while (total_error > distToStopBlock) {
        pros::delay(20);
    }
    return;
}
