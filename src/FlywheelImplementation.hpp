#include "main.h"
#include "globals.hpp"
#include "pidVelSystem.hpp"

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

void setFlywheelRPM(double rpm);

void flywheelControl();