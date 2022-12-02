#include <chrono>

#ifndef _MISC_UTILS_H_
#define _MISC_UTILS_H_

namespace misc {
/**
*   @brief Calculate remainder (modulos) for negative numbers too
*   
*   @param val value to use
*   @param size remainder size
*   @return int remainder (val%size)
*/
int remainder(int val, int size);

/**
*   @brief Calculate remainder (modulos) for negative floats
*   
*   @param val value to use
*   @param size remainder size
*   @return float remainder (val%size)
*/
float remainder_f(float val, float size);
} // namespace misc

#endif