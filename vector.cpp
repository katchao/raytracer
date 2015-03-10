#include "vector.h"

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(int ix, int iy, int iz) {
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

// prints out vectors in the form of <x, y, z>
std::ostream& operator<<(std::ostream &strm, const Vector &v) {
  return strm << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}
/*
std::ostream& operator<<(std::ostream &strm, Vector v) {
  return strm << "<" << v.x << ", " << v.y << ", " << v.z << ">";
}*/