#include "Vector3D.h"

Vector3D::Vector3D(double xValue, double yValue, double zValue)
	: x(xValue), y(yValue), z(zValue) {}

Vector3D Vector3D::operator+(const Vector3D& right) const
{
	return Vector3D(this->x + right.x, this->y + right.y, this->z + right.z);
}

Vector3D Vector3D::operator-(const Vector3D& right) const
{
	return Vector3D(this->x - right.x, this->y - right.y, this->z - right.z);
}

double Vector3D::operator*(const Vector3D& right) const
{
	return (this->x * right.x) + (this->y * right.y) + (this->z * right.z);
}

Vector3D Vector3D::operator^(const Vector3D& right) const
{
	return Vector3D(this->y * right.z - this->z * right.y, this->z * right.x - this->x * right.z, this->x * right.y - this->y * right.x);
}

Vector3D Vector3D::operator*(double scalar) const
{
	return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

double Vector3D::GetX() const
{
	return this->x;
}

double Vector3D::GetY() const
{
	return this->y;
}

double Vector3D::GetZ() const
{
	return this->z;
}

double Vector3D::Length() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vector3D::Normalize()
{
	double length = this->Length();
	if (length != 0) {
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}
}