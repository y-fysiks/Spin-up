#include "main.h"
#include "globals.hpp"

//is red method for color detection and rollers
bool isRed(int hue) {
    if (hue > 310 || hue < 120) return true;
    return false;
}