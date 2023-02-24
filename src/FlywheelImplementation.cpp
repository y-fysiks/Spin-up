#include "FlywheelImplementation.hpp"
#include <atomic>

double flywheelRatio = 1;
velPID pid(260, 30, 20.6, 0.9);// kP, kD, kF, emaAlpha
//original values 30, 0, 20, 0.9
emaFilter rpmFilter(0.15);
double motorSlew = 300;

std::atomic<double> targetRPM = 0;
double currentRPM = 0;
double lastPower = 0;
double motorPower = 0;
bool disableFlywheel = false;

void setFlywheelRPM(int rpm) {
    targetRPM = 1.0 * rpm;
    if (rpm == 0) disableFlywheel = true;
    else disableFlywheel = false;
}

void flywheelControl() {
  while(true) {
    
    currentRPM = rpmFilter.filter(flywheel.get_actual_velocity() * flywheelRatio);
    
    motorPower = pid.calculate(targetRPM.load(), currentRPM);
    
    if(motorPower <= 0) motorPower = 0; //Prevent motor from spinning backward
    
    //Give the motor a bit of a starting boost
    //if(motorPower > lastPower && lastPower < 1000 && motorPower > 1000) lastPower = 1000;
    
    //This slews the motor by limiting the rate of change of the motor speed
    //double increment = motorPower - lastPower;
    //if(std::abs(increment) > motorSlew) motorPower = lastPower + (motorSlew * sgn(increment));
    lastPower = motorPower;
    
    if (disableFlywheel) motorPower = 0;
    flywheel.move_voltage((int) motorPower);
    //flywheelVoltage((int) motorPower);
    
    pros::screen::print(TEXT_SMALL, 6, "RPM: %.2f   Power: %.2f   Error: %.2f", currentRPM, motorPower, pid.getError()); //print X, Y and angle after each compute
    printf("%.2f\n", currentRPM);
    pros::delay(20);
  }
}
