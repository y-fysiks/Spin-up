#include "motionAlgos.hpp"
#include "greatapi/units/angle_units/angle_diff.hpp"
#include "greatapi/units/angle_units/srad.hpp"
#include "odometry.hpp"
#include <utility>

purePursuit::Target* pptarget = new purePursuit::Target();

purePursuit::Bot talos(pptarget);

void ptranslatevl(std::pair<double, double> coords[], int pathLen, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock) {    
    
    if (goHeading) {
        if (reverseHeading) {
            rotate(90 - (atan2(coords[0].second - location.y, coords[0].first - location.x) + PI) / PI * 180.0, 0);
        } else {
            rotate(90 - (atan2(coords[0].second - location.y, coords[0].first - location.x)) / PI * 180.0, 0);
        }
    }
    purePursuit::Node nodes[pathLen + 1];

    nodes[0].xPos = (double) targetPos.x;
    nodes[0].yPos = (double) targetPos.y;

    for (int i = 1; i <= pathLen; i++) {
        nodes[i].xPos = coords[i - 1].first;
        nodes[i].yPos = coords[i - 1].second;
    }

    std::pair<purePursuit::Node, purePursuit::Node> path[pathLen];
    for (int i = 0; i < pathLen; i++) {
        path[i].first = nodes[i];
        path[i].second = nodes[i + 1];
    }

    reverseDrive = revDrive;
    voltageCap = maxVoltage;
    
    translating = true;
    
    if (distToStopBlock == 0) distToStopBlock = 1;

    std::pair<double, double> targetPair;
    pptarget->newPath(path, pathLen);

    int stuckTimer = 0;
    double prevError = total_error;
    pros::delay(20);

    talos.updatePosition(location.x, location.y);

    greatapi::SRAD pathAngle = greatapi::SRAD(0);

    bool lastIn = false;


    //IAngle->factor = 0;


    // initialize the ksi to 5% as a parameter - then we can fine tune it 
    // line 40 - syntax ** for conditional??

    while (stuckTimer < 75) { // Keep looping until at target, abort to next movement if stuck for 1.5 seconds
        if (fabs(total_error - prevError) < 0.08) {
            stuckTimer++;
        } else {
            stuckTimer = 0;
        }
        prevError = total_error;

        pros::screen::print(TEXT_MEDIUM, 7, "Stage: %d  targetPos X: %.2f  Y: %.2f\n", pptarget->stage, targetPair.first, targetPair.second);
        pros::screen::print(TEXT_MEDIUM, 8, "xTrans: %.2f yTrans: %.2f\n", pptarget->xTrans, pptarget->yTrans);
        pros::screen::print(TEXT_MEDIUM, 9, "xoy: %.2f\n", pptarget->xoy);
        // printf("stage: %d xPos: %.2f yPos: %.2f\nxTrans: %.2f yTrans: %.2f\nxoy: %.2f\n", pptarget->stage, pptarget->xPos, pptarget->yPos, pptarget->xTrans, pptarget->yTrans, pptarget->xoy);


        pptarget->updatePosition();
        if (talos.btDist() > visionRadius) {
            pptarget->bind(talos.btDist());
        }
        targetPair = talos.updatePosition(location.x, location.y);

        if (!lastIn && fabs(greatapi::findDiff(location.angle, targetPos.angle)) < greatapi::degrees(18)) {
            printf("T %.2f\n", (double) location.angle * 180 / PI);
            IAngle = new greatapi::Integral(kIAngle, std::pair(1000, -1000));
            lastIn = true;
        }

        targetPos.x = targetPair.first;
        targetPos.y = targetPair.second;

        pros::delay(50);

        if (pptarget->atPathEnd) {
            if (total_error < distToStopBlock) break;
        }

       IAngle = new greatapi::Integral(kIAngle, std::pair(1000, -1000));
    
    }

    return;

}

void ptranslate(std::pair<double, double>*coords[], bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock) {
    
}

