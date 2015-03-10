#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

using namespace std;

class Vector {
  public:
	float x, y, z;

	Vector();
	Vector(int, int, int);

    void add (Vector, Vector);
	void subtract (Vector, Vector);
	void scalar_multiply (Vector, float);
	void scalar_divide (Vector, float);
	void normalize();
	float dot_product(Vector);
	//Vector subtract_two_points(Point, Point);
};

#endif