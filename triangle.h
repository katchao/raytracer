#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class Intersection;

class Triangle {
	public:
	  	Vector v1, v2, v3;//3 vertices

		Triangle();
		Triangle(Vector, Vector, Vector);
		bool intersect(Ray&, float*, Intersection*);
		bool intersectP(Ray&);
};

#endif