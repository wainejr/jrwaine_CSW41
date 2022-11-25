#include <chrono>

#ifndef _MISC_UTILS_H_
#define _MISC_UTILS_H_

namespace misc {
typedef std::chrono::steady_clock::time_point t_time;

t_time get_current_time();

float get_diff_time_sec(t_time start, t_time end);

int remainder(int val, int size);

float remainder_f(float val, float size);
} // namespace misc

#endif