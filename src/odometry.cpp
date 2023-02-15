#include "odometry.hpp"
#include "pros/rtos.hpp"

/**
 * odometry function
 * 
 */
void odometryLooper() {
    pros::screen::set_pen(COLOR_GREEN);
    right_encoder->reset();
    left_encoder->reset();
    rear_encoder->reset();
    // odom.globaloffset = PI;
    while (true) {
        location = odom.calculateposition(location);
        pros::screen::print(TEXT_SMALL, 3, "X: %.2f   Y: %.2f", location.x, location.y); //print X, Y and angle after each compute
        pros::screen::print(TEXT_SMALL, 2, "Angle: %.2f", location.angle / PI * 180);
        //printf("X %.2f   Y %.2f   Angle %.2f\n", (double) location.x, (double) location.y, (double) (location.angle / PI * 180));
        pros::screen::print(TEXT_SMALL, 1, "leftTW: %.2f  rightTW: %.2f  backTW: %.2f", left_encoder->get_distance(), right_encoder->get_distance(), rear_encoder->get_distance());

        pros::delay(5);
    }
    return;
}

/**
 * function to be run in a task to move the robot the the target position
 * 
 */
void position_control() {
    std::vector<greatapi::controlelement *> PIDYElements;
    //TODO TUNE PID FOR Y
    greatapi::controlelement *PY = new greatapi::Proportional(1100, std::pair(__INT_MAX__, -__INT_MAX__));          PIDYElements.push_back(PY);
    greatapi::controlelement *IY = new greatapi::Integral(0, std::pair(__INT_MAX__, -__INT_MAX__));                 PIDYElements.push_back(IY);
    greatapi::controlelement *DY = new greatapi::Derivative(1100, std::pair(__INT_MAX__, -__INT_MAX__));            PIDYElements.push_back(DY);

    greatapi::control_loop PIDY(PIDYElements, std::pair(12000, -12000));


    std::vector<greatapi::controlelement *> PIDAngleElements;
    //TODO TUNE PID FOR ANGLE
    greatapi::controlelement *PAngle = new greatapi::Proportional(20000, std::pair(__INT_MAX__, -__INT_MAX__));     PIDAngleElements.push_back(PAngle);
    greatapi::controlelement *IAngle = new greatapi::Integral(3000, std::pair(4500, -4500));                        PIDAngleElements.push_back(IAngle);
    greatapi::controlelement *DAngle = new greatapi::Derivative(15000, std::pair(__INT_MAX__, -__INT_MAX__));       PIDAngleElements.push_back(DAngle);

    greatapi::control_loop PIDAngle(PIDAngleElements, std::pair(11000, -11000));

    targetPos = location;
    
    while (true) {
        //current position is location variable
        //target position is targetPos variable
        total_error = sqrt(pow(targetPos.x - location.x, 2) + pow(targetPos.y - location.y, 2));

        greatapi::coord error(location, targetPos);
        error.self_transform_matrix(greatapi::SRAD(-1.0 * location.angle));

        if (translating && fabs((double) error.x) > 0.8) {
            if (reverseDrive) targetPos.angle = greatapi::SRAD(atan2(targetPos.y - location.y, targetPos.x - location.x) + PI / 2);
            else targetPos.angle = greatapi::SRAD(atan2(targetPos.y - location.y, targetPos.x - location.x) - PI / 2);
        }
        if (total_error < 2) {
            translating = false;
        }
        
        double yMove = PIDY.update(error.y, 0);
        double anglePow = -PIDAngle.update(greatapi::findDiff(location.angle, targetPos.angle), 0);

        if (yMove > voltageCap) {
            yMove = voltageCap;
        } else if (yMove < -voltageCap) {
            yMove = -voltageCap;
        }

        if (anglePow > voltageCap) {
            anglePow = voltageCap;
        } else if (anglePow < -voltageCap) {
            anglePow = -voltageCap;
        }
        

        double lPower = yMove + anglePow;
        double rPower = yMove - anglePow;

        if (moveDrive) {
            l1_motor.move_voltage(lPower);
            l2_motor.move_voltage(lPower);
            l3_motor.move_voltage(lPower);
            r1_motor.move_voltage(rPower);
            r2_motor.move_voltage(rPower);
            r3_motor.move_voltage(rPower);
        } else {
            
        }
        
        pros::screen::print(TEXT_SMALL, 4, "Angle target: %.2f\n", targetPos.angle / PI * 180);
        pros::screen::print(TEXT_SMALL, 5, "Total error: %.2f\n", total_error);
        pros::delay(5);
    }
    return;
}

/**
 * rotates the bot to the specified absolute heading. Blocks execution until the bot is at the specified heading.
 * 
 * \param angle the absolute heading to rotate to
 * \param errorStop DEGREES the function will stop the bot if the error is greater than the error threshold. IF 0, default is 2 degrees
 */
void rotate(double angleDeg, double errorStop) {
    translating = false;
    voltageCap = 12000;
    greatapi::SRAD angle = greatapi::SRAD((-1.0 * angleDeg) * PI / 180.0);
    targetPos.angle = angle;
    errorStop = errorStop == 0 ? 2 : errorStop;
    while (fabs(greatapi::findDiff(location.angle, targetPos.angle)) > greatapi::degrees(errorStop)) {
        pros::delay(50);
    }
    return;
}

#define defaultMaxVolts 10000

/**
 * translates the robot to absolute coordinates. DOES NOT BLOCK EXECUTION
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param maxVoltage the maximum voltage to send to the motors
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void translatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading) {
    if (goHeading) {
        if (reverseHeading) {
            rotate(90 - (atan2(y - location.y, x - location.x) + PI) / PI * 180.0, 0);
        } else {
            rotate(90 - (atan2(y - location.y, x - location.x)) / PI * 180.0, 0);
        }
    }
    targetPos.x = x;
    targetPos.y = y;
    reverseDrive = revDrive;
    voltageCap = maxVoltage;
    total_error = sqrt(pow(targetPos.x - location.x, 2) + pow(targetPos.y - location.y, 2));
    translating = true;
    if (reverseDrive) targetPos.angle = greatapi::SRAD(atan2(targetPos.y - location.y, targetPos.x - location.x) + PI / 2);
    else targetPos.angle = greatapi::SRAD(atan2(targetPos.y - location.y, targetPos.x - location.x) - PI / 2);

    return;
}

/**
 * translates the robot to absolute coordinates. DOES NOT BLOCK EXECUTION
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void translate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading) {
    translatevl(x, y, revDrive, defaultMaxVolts, goHeading, reverseHeading);
    return;
}

/**
 * translates the robot to absolute coordinates. Blocks execution. 
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param maxVoltage the maximum voltage to send to the motors
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target
 * \param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.8
 */
void translatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock) {
    translatevl(x, y, revDrive, maxVoltage, goHeading, reverseHeading);
    distToStopBlock = distToStopBlock == 0 ? 1 : distToStopBlock;
    while (fabs(total_error) > distToStopBlock) {
        pros::delay(20);
    }
    return;
}

/**
 * translates the robot to absolute coordinates. Blocks execution. 
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target
 * \param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.8
 */
void translate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock) {
    translatevl(x, y, revDrive, defaultMaxVolts, goHeading, reverseHeading, distToStopBlock);
    return;
}

/**
 * translates the robot to relative coordinates. DOES NOT BLOCK EXECUTION
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param maxVoltage the maximum voltage to send to the motors
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void rtranslatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading) {
    translatevl(((double) targetPos.x) + x, ((double) targetPos.y) + y, revDrive, maxVoltage, goHeading, reverseHeading);
}
/**
 * translates the robot to relative coordinates. DOES NOT BLOCK EXECUTION
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void rtranslate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading) {
    translate(((double) targetPos.x) + x, ((double) targetPos.y) + y, revDrive, goHeading, reverseHeading);
}
/**
 * translates the robot to relative coordinates. Blocks execution. 
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param maxVoltage the maximum voltage to send to the motors
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target
 * \param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.8
 */
void rtranslatevl(double x, double y, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock) {
    translatevl(((double) targetPos.x) + x, ((double) targetPos.y) + y, revDrive, maxVoltage, goHeading, reverseHeading, distToStopBlock);
}
/**
 * translates the robot to relative coordinates. Blocks execution. 
 * 
 * \param x the x coordinate to translate to
 * \param y the y coordinate to translate to
 * \param revDrive whether or not to reverse the drive direction
 * \param goHeading whether or not to point towards the target
 * \param reverseHeading whether or not to invert the heading when pointing towards the target
 * \param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.8
 */
void rtranslate(double x, double y, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock) {
    translate(((double) targetPos.x) + x, ((double) targetPos.y) + y, revDrive, goHeading, reverseHeading, distToStopBlock);
}

void rtranslateDist(double dist, bool revDrive, double maxVoltage) {
    double x = (dist * cos(targetPos.angle));
    double y = (dist * sin(targetPos.angle));
    if (revDrive) {
        x = -x;
        y = -y;
    }
    rtranslatevl(x, y, revDrive, maxVoltage, false, false);
}
void rtranslateDist(double dist, bool revDrive) {
    rtranslateDist(dist, revDrive, defaultMaxVolts);
}
