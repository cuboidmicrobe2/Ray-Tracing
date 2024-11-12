#include "Vector3D.h"

Vector3D::Vector3D(double xValue, double yValue, double zValue)
{
}

Vector3D Vector3D::operator+(const Vector3D& right) const
{
	return Vector3D(0.0, 0.0, 0.0);
}

Vector3D Vector3D::operator-(const Vector3D& right) const
{
	return Vector3D(0.0, 0.0, 0.0);
}

double Vector3D::operator*(const Vector3D& right) const
{
	return 0.0;
}

Vector3D Vector3D::operator^(const Vector3D& right) const
{
	return Vector3D(0.0, 0.0, 0.0);
}

Vector3D Vector3D::operator*(double scalar) const
{
	return Vector3D(0.0, 0.0, 0.0);
}

double Vector3D::GetX() const
{
	return 0.0;
}

double Vector3D::GetY() const
{
	return 0.0;
}

double Vector3D::GetZ() const
{
	return 0.0;
}

double Vector3D::Length() const
{
	return 0.0;
}

void Vector3D::Normalize()
{
}
