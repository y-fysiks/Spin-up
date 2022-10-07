/**
 * @brief odometry function
 * 
 */
void odometryLooper();

/**
 * @brief function to be run in a task to move the robot the the target position
 * 
 */
void position_control();

/**
 * @brief translates the robot to absolute coordinates. DOES NOT BLOCK EXECUTION
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void translate(double x, double y, bool goHeading, bool reverseHeading) ;

/**
 * @brief translates the robot to absolute coordinates. Blocks execution. 
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target
 * @param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.3
 */
void translate(double x, double y, bool goHeading, bool reverseHeading, double distToStopBlock);