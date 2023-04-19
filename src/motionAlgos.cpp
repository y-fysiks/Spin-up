#include "motionAlgos.hpp"


void ptranslatevl(std::pair<double, double> coords[], int nodeLen, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock) {
    Node nodes[nodeLen];
    for (int i = 0; i < nodeLen; i++) {
        nodes[i].xPos = coords[i].first;
        nodes[i].yPos = coords[i].second;
    }

    std::pair<Node, Node>* path[nodeLen - 1];
    for (int i = 0; i < nodeLen - 1; i++) {
        path[i]->first = nodes[i];
        path[i]-> second = nodes[i + 1];
    }
    
    pptarget->newPath(location.x, location.y, path, nodeLen - 1);
    
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
        talos.updatePosition();

        if (pptarget->stage == nodeLen - 2) {
            if (total_error < distToStopBlock) break;
        }
        pros::delay(20);
    }

    return;

}

void ptranslate(std::pair<double, double>*coords[], bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock) {
    
}

