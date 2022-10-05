void odometryLooper();
void position_control();
void rotate(double angleDeg);
void rotate(double angleDeg, double errorStop);
void translate(double x, double y, bool goHeading, bool reverseHeading);
void translate(double x, double y, bool goHeading, bool reverseHeading, double distToStopBlock);