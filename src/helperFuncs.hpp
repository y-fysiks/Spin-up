// functions to get angle given current position and target position
/**
 * @brief dot product of two vectors
 * 
 * @param a x component of first vector
 * @param b y component of first vector
 * @param c x component of second vector
 * @param d y component of second vector
 * @return long double result of dot product
 */
long double dot(long double a, long double b, long double c, long double d);

/**
 * @brief sign function
 * 
 * @param x number to get sign of
 * @return int sign of x
 */
int sgn(long double x);

// b 0 a b
// d 0 c d
/**
 * @brief cross product of two vectors
 * 
 * @param a x component of first vector
 * @param b y component of first vector
 * @param c x component of second vector
 * @param d y component of second vector
 * @return int sign of cross product
 */
int cross(long double a, long double b, long double c, long double d);

/**
 * @brief Get the angle object
 * 
 * @param targetx x component of target vector
 * @param targety y component of target vector
 * @return long double 
 */
long double get_angle(long double targetx, long double targety);