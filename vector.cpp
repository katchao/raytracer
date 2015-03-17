#include "vector.h"

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(int ix, int iy, int iz) {
	x = (float) ix;
	y = (float) iy;
	z = (float) iz;
}

Vector::Vector(float ix, float iy, float iz) {
	x = ix;
	y = iy;
	z = iz;
}

void Vector::add(Vector v1, Vector v2) {
	x = v1.x + v2.x;
	y = v1.y + v2.y;
	z = v1.z + v2.z;
}

void Vector::subtract(Vector v1, Vector v2) {
	x = v1.x - v2.x;
	y = v1.y - v2.y;
	z = v1.z - v2.z;
}

void Vector::scalar_multiply(Vector v, float scalar) {
	x = v.x * scalar;
	y = v.y * scalar;
	z = v.z * scalar;
}

void Vector::scalar_divide(Vector v, float scalar) {
	x = v.x / scalar;
	y = v.y / scalar;
	z = v.z / scalar;
}

Vector Vector::operator+(const Vector& v) {
	Vector result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	result.z = this->z + v.z;
	return result;
}

Vector Vector::operator-(const Vector& v) {
	Vector result;
	result.x = this->x - v.x;
	result.y = this->y - v.y;
	result.z = this->z - v.z;
	return result;
}

Vector Vector::operator*(const Vector& v) {
	Vector result;
	result.x = this->x * v.x;
	result.y = this->y * v.y;
	result.z = this->z * v.z;
	return result;
}

Vector Vector::operator*(float scalar) {
	Vector result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	result.z = this->z * scalar;
	return result;
}

Vector Vector::operator/(const Vector& v) {
	Vector result;
	result.x = this->x / v.x;
	result.y = this->y / v.y;
	result.z = this->z / v.z;
	return result;
}

Vector Vector::operator/(float scalar) {
	Vector result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	result.z = this->z / scalar;
	return result;
}

void Vector::normalize() {
	float magnitude = pow(x, 2) + pow(y, 2) + pow(z, 2);
	magnitude = sqrt(magnitude);
	
	if( magnitude > 0) {
		x = x / magnitude;
		y = y / magnitude;
		z = z / magnitude;
	}
}

float Vector::dot_product(Vector v) {
	return x * v.x + y * v.y + z * v.z;
}

void Vector::print() {
	cout << "<" << x << ", " << y << ", " << z << ">";
}

float dot_product(Vector v1, Vector v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}