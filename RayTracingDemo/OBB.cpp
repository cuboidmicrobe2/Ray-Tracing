#include "OBB.h"

#include <initializer_list>

#include "MathFuncs.h"

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

{
}

bool OBB::Intersection(const Ray& ray, double& t) {
	double tMin = -INFINITY;
	double tMax = INFINITY;
	const double MARGIN = 1e-5;
	Vector3D p = this->center - ray.origin;
	Vector3D vectorArray[3] = { this->u, this->v, this->w };
	double widthArray[3] = { this->width, this->height, this->depth };
	for (int i = 0; i < 3; i++) {
		double e = vectorArray[i] * p;
		double f = vectorArray[i] * ray.direction;
		if (fabs(f) > MARGIN) {
			double t1 = (e + widthArray[i]) / f;
			double t2 = (e - widthArray[i]) / f;
			if (t1 > t2) std::swap(t1, t2);
			if (t1 > tMin) tMin = t1;
			if (t2 < tMax) tMax = t2;
			if (tMin > tMax || tMax < 0) return false;
		}
		else if (-e - widthArray[i] > 0 || -e + widthArray[i] < 0) return false;
	}

	if (tMin > 0) {
		t = tMin;
		return true;
	}

	else if (tMax > 0) {
		t = tMax;
		return true;
	}

	return false;
}