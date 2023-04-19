#include "odometry.hpp"
#include "globals.hpp"
#include "purePursuit.hpp"

inline Target* pptarget = new Target();

inline Bot talos(pptarget);


void ptranslate(std::pair<double, double> coords[], int nodeLen, bool revDrive, bool goHeading, bool reverseHeading, double distToStopBlock);

void ptranslatevl(std::pair<double, double> coords[], int nodeLen, bool revDrive, double maxVoltage, bool goHeading, bool reverseHeading, double distToStopBlock);
