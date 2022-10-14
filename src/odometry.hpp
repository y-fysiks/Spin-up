/**
 * odometry function
 * 
 */
void odometryLooper();

/**
 * function to be run in a task to move the robot the the target position
 * 
 */
void position_control();

/**
 * rotates the bot to the specified absolute heading. DOES NOT BLOCK EXECUTION
 * 
 * @param angle the absolute heading to rotate to
 */
void rotate(double angleDeg);

/**
 * rotates the bot to the specified absolute heading. Blocks execution until the bot is at the specified heading.
 * 
 * @param angle the absolute heading to rotate to
 * @param errorStop DEGREES the function will stop the bot if the error is greater than the error threshold. IF 0, default is 2 degrees
 */
void rotate(double angleDeg, double errorStop);

/**
 * translates the robot to absolute coordinates. DOES NOT BLOCK EXECUTION
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target.
 */
void translate(double x, double y, bool goHeading, bool reverseHeading);

/**
 * translates the robot to absolute coordinates. Blocks execution. 
 * 
 * @param x the x coordinate to translate to
 * @param y the y coordinate to translate to
 * @param goHeading whether or not to point towards the target
 * @param reverseHeading whether or not to invert the heading when pointing towards the target
 * @param distToStopBlock the distance from target to stop blocking the function. IF 0, it will default to 0.3
 */
void translate(double x, double y, bool goHeading, bool reverseHeading, double distToStopBlock);