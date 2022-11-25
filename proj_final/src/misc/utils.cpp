#include "utils.h"

misc::t_time misc::get_current_time()
{
    t_time now = std::chrono::high_resolution_clock::now();
    return now;
}

float misc::get_diff_time_sec(t_time start, t_time end)
{
    auto diff = (start - end);
    auto diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    return diff_ms / 1000.0f;
}

int misc::remainder(int val, int size)
{
    if (val < size && val > 0) {
        return val;
    }
    return (val + size) % size;
}

float misc::remainder_f(float val, float size)
{
    if (val < size && val > 0) {
        return val;
    }
    while (val < 0) {
        val += size;
    }
    return val - ((int)(val / size)) * size;
}
