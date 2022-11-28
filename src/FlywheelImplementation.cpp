#include "FlywheelImplementation.hpp"

double flywheelRatio = 1;
velPID pid(35, 0, 20, 0.9);// kP, kD, kF, emaAlpha
emaFilter rpmFilter(0.15);
double motorSlew = 300;

double targetRPM = 0;
double currentRPM = 0;
double lastPower = 0;
double motorPower = 0;
bool disableFlywheel = false;

void setFlywheelRPM(double rpm) {
    targetRPM = rpm;
    if (rpm == 0) disableFlywheel = true;
    else disableFlywheel = false;
}

void flywheelControl() {
  while(true) {
    
    currentRPM = rpmFilter.filter(flywheel_1.get_actual_velocity() * flywheelRatio);
    
    motorPower = pid.calculate(targetRPM, currentRPM);
    
    if(motorPower <= 0) motorPower = 0; //Prevent motor from spinning backward
    
    //Give the motor a bit of a starting boost
    if(motorPower > lastPower && lastPower < 10 && motorPower > 10) lastPower = 10;
    
    //This slews the motor by limiting the rate of change of the motor speed
    double increment = motorPower - lastPower;
    if(std::abs(increment) > motorSlew) motorPower = lastPower + (motorSlew * sgn(increment));
    lastPower = motorPower;
    
    if (disableFlywheel) motorPower = 0;
    flywheelVoltage(motorPower);
    
    pros::screen::print(TEXT_SMALL, 4, "RPM: %.2f   Power: %.2f   Error: %.2f", currentRPM, motorPower, pid.getError()); //print X, Y and angle after each compute

    pros::delay(20);
  }
}
