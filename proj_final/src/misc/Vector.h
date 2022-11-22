#include <stdint.h>

#ifndef _MISC_VECTOR_H_
#define _MISC_VECTOR_H_
namespace misc {
/**
 *   @brief Representation of a vector-2D of given type
 *
 *   @tparam Type of vector (as float, double, int, etc.)
 */
template <typename T>
class Vector {

public:
    T x;
    T y;

    /**
     *   @brief Construct a new Vector object
     *
     *   @param x Vector's x value
     *   @param y Vector's y value
     */
    Vector(const T x, const T y)
    {
        this->x = x;
        this->y = y;
    }
    Vector(const T p[2])
    {
        this->x = p[0];
        this->y = p[1];
    }
    Vector()
    {
        this->x = 0;
        this->y = 0;
    }

    /**
     *   @brief Add vector value to this
     *
     *   @param p Vector values to add this
     */
    void add(Vector<T> p)
    {
        this->x += p.x;
        this->y += p.y;
    }

    /**
     *   @brief Dot product between this vector and the given one
     *
     *   @param p Vector to calculate dot product
     */
    Vector<T> dot(Vector<T> p)
    {
        return Vector<T>(p.x * this->x, p.y * this->y);
    }

    /**
     *   @brief Multiply this vector and scalar
     *
     *   @param p Scalar value to multiply
     */
    Vector<T> mul(T v)
    {
        return Vector<T>(v * this->x, v * this->y);
    }
};
} // namespace misc
#endif