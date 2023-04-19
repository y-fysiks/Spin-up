#ifndef BOT_PUREP_HPP
#define BOT_PUREP_HPP

#include "target.hpp"
#include "main.h"
#include "globals.hpp"
#include "odometry.hpp"

struct Bot {
    double xPos = 0, yPos = 0;
    
    Target target;
    
    int stage = 0;
    bool hnorth = true, heast = true;

    Bot(Target *target_) {
        target = *target_;
    }

    void updatePosition() {
        xPos = location.x;
        yPos = location.y;

        targetPos.x = target.xPos;
        targetPos.y = target.yPos;
    }

    double btDist() {
        return sqrt(pow(xPos - target.xPos, 2) + pow(yPos - target.yPos, 2));
    }

} ;

#endif