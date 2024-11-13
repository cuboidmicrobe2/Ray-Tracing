#include "Sphere.h"

#include <cmath>

Sphere::Sphere(const Vector3D& colour, const Vector3D c, double r)
    : Shape(colour), center(c), radius(r) {}

bool Sphere::Intersection(const Ray& ray, double& t) {
  Vector3D rayOriginToCenter = this->center - ray.origin;
  double rayToSphereCenterLineLength = rayOriginToCenter * ray.direction;

  if (rayToSphereCenterLineLength < 0 &&
      rayOriginToCenter.squared() > squared(this->radius))
    return false;

  double squaredRayOrthogonalLengthToCenter =
      rayOriginToCenter.squared() - squared(rayToSphereCenterLineLength);

  if (squaredRayOrthogonalLengthToCenter > squared(this->radius)) return false;

  double rayDistanceFromCenterLineToSurface =
      sqrt(squared(this->radius) - squaredRayOrthogonalLengthToCenter);

  if (rayOriginToCenter.squared() > squared(this->radius)) {
    t = rayToSphereCenterLineLength - rayDistanceFromCenterLineToSurface;
  }

  else {
    t = rayToSphereCenterLineLength + rayDistanceFromCenterLineToSurface;
  }

  return true;
}