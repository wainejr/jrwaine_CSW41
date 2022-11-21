#include "./vector.h"

using namespace misc;

template <class T> void Vector<T>::Vector(T x, T y) {
  this->x = x;
  this->y = y;
}

template <class T> void Vector<T>::add(Vector<T> v) {
  this.x += v.x;
  this.y += v.y;
}

template <class T> Vector<T> Vector<T>::dot(Vector<T> v) {
  return Vector<T>(v.x * this.x, v.y * this.y);
}

template <class T> Vector<T> Vector<T>::mul(T v) {
  return Vector<T>(v * this.x, v * this.y);
}
