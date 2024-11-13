#include "Plane.h"

Plane::Plane(const Vector3D & colour, const Vector3D & p, const Vector3D & n) 
	: Shape(colour), point(p), normal(n)
{
	// Implement constructor logic here
}

bool Plane::Intersection(const Ray & ray, double & t)
{
	// Implement intersection logic here
	double denom = ray.direction * this->normal;

	if (aproxEqual(denom, 0, 0.001)) return false;

	Vector3D vectorFromRayOriginToPlane = this->point - ray.origin;

	t = (vectorFromRayOriginToPlane * this->normal) / denom;

	return t > 0;
}