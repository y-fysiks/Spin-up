#include "pidVelSystem.hpp"

velPID::velPID(double Kp, double Kd, double Kf, double emaAlpha)
: m_dFilter(emaAlpha) {
  m_Kp = Kp;
  m_Kd = Kd;
  m_Kf = Kf;
}

double velPID::calculate(double wantedRPM, double currentRPM) {
  m_Error = wantedRPM - currentRPM;

  m_derivative = (m_Error - m_lastError);
  m_lastError = m_Error;
  m_derivative = m_dFilter.filter(m_derivative);

  double finalPower = (m_Error * m_Kp) + (m_derivative * m_Kd) + (wantedRPM * m_Kf);

  if(fabs(finalPower) > 12000) { finalPower = sgn(finalPower) * 12000; }

  return finalPower;
}

void velPID::setGains(double Kp, double Kd, double Kf, double emaAlpha) {
  m_Kp = Kp;
  m_Kd = Kd;
  m_Kf = Kf;

  m_dFilter.setGains(emaAlpha);
}

double velPID::getError() { return m_Error; }