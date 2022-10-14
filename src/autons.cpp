#include "main.h"
#include "globals.hpp"
#include "helperFuncs.hpp"
#include "odometry.hpp"

void redLeft() {
    //red left
    red_team = true;
}

void redRight() {
    //red right
    red_team = true;
}

void blueLeft() {
    //blue left
    red_team = false;
}

void blueRight() {
    //blue right
    red_team = false;
}

void skills() {
    //skills RED TEAM
    red_team = true;
}