#include <stdint.h>

namespace misc {
/**
 *   @brief Representation of a vector-2D of given type
 *
 *   @tparam Type of vector (as float, double, int, etc.)
 */
template <class T> class Vector {

public:
  T x;
  T y;

  /**
   *   @brief Construct a new Vector object
   *
   *   @param x Vector's x value
   *   @param y Vector's y value
   */
  Vector(T x, T y);

  /**
   *   @brief Add vector value to this
   *
   *   @param p Vector values to add this
   */
  void add(Vector p);

  /**
   *   @brief Dot product between this vector and the given one
   *
   *   @param p Vector to calculate dot product
   */
  Vector dot(Vector p);

  /**
   *   @brief Multiply this vector and scalar
   *
   *   @param p Scalar value to multiply
   */
  Vector mul(T v);
};
} // namespace misc