#include "odometry.hpp"
#include "globals.hpp"

void ptranslate(std::pair<double, double> coords[], int nodeLen, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock);

void ptranslatevl(std::pair<double, double> coords[], int nodeLen, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock);