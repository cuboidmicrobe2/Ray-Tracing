#include "OBB.h"

#include <initializer_list>
// #include "MathFuncs.h"

OBB::OBB(const Vector3D& colour, const Vector3D& centerPoint, const Vector3D& u,
         const Vector3D& v, const Vector3D& w, double width, double height,
         double depth)
    : Shape(colour),
      center(centerPoint),
      u(u),
      v(v),
      w(w),
      width(width),
      height(height),
      depth(depth)

{}

bool OBB::Intersection(const Ray& ray, double& t) {
  
  return true;
}
