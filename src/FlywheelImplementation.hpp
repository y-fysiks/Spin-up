#include "main.h"
#include "globals.hpp"
#include "pidVelSystem.hpp"

#ifndef HELPERFUNCS_HPP
#define HELPERFUNCS_HPP

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

void setFlywheelRPM(int rpm);

void flywheelControl();

#endif