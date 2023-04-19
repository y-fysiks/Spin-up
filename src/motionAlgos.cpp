#include "motionAlgos.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include <utility>


void ptranslatevl(std::pair<double, double> coords[], int pathLen, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock) {
    purePursuit::Node nodes[pathLen + 1];

    for (int i = 1; i <= pathLen; i++) {
        nodes[i].xPos = coords[i].first;
        nodes[i].yPos = coords[i].second;
    }

    nodes[0].xPos = location.x;
    nodes[0].yPos = location.y;

    std::pair<purePursuit::Node, purePursuit::Node> path[pathLen];
    for (int i = 0; i < pathLen; i++) {
        path[i].first = nodes[i];
        path[i].second = nodes[i + 1];
    }
    
    pptarget->newPath(location.x, location.y, path, pathLen);
    
    if (goHeading) {
        if (reverseHeading) {
            rotate(90 - (atan2(coords[0].second - location.y, coords[0].first - location.x) + PI) / PI * 180.0, 0);
        } else {
            rotate(90 - (atan2(coords[0].second - location.y, coords[0].first - location.x)) / PI * 180.0, 0);
        }
    }
    reverseDrive = revDrive;
    voltageCap = maxVoltage;
    
    translating = true;
    
    if (distToStopBlock == 0) distToStopBlock = 1;
    int stuckTimer = 0;
    double prevError = total_error;
    pros::delay(20);

    std::pair<double, double> targetPair;
    while (stuckTimer < 75) { // Keep looping until at target, abort to next movement if stuck for 1.5 seconds
        if (fabs(total_error - prevError) < 0.08) {
            stuckTimer++;
        } else {
            stuckTimer = 0;
        }
        prevError = total_error;

        pptarget->updatePosition();
        if (talos.btDist() > visionRadius) {
            pptarget->bind(talos.btDist());
        }
        targetPair = talos.updatePosition(location.x, location.y);

        if (pptarget->stage == pathLen - 1) {
            if (total_error < distToStopBlock) break;
        }

        pros::screen::print(TEXT_MEDIUM, 7, "Stage: %d  targetPos X: %.2f  Y: %.2f", pptarget->stage, targetPair.first, targetPair.second);

        pros::delay(30);
    }

    return;

}

void ptranslate(std::pair<double, double>*coords[], bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock) {
    
}

