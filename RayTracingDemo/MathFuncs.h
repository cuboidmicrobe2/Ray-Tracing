#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include <cmath>
#include <algorithm>

#include "Vector3D.h"

inline bool aproxEqual(double left, double right, double margin) {
  return fabs(left - right) < margin;
}

inline double squared(double valueToSquare) {
  return valueToSquare * valueToSquare;
}

#endif  // !MATH_FUNCS_H