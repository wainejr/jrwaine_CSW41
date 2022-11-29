#include "utils.h"

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
