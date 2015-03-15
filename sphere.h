#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"
#include "primitive.h"

using namespace std;

class Intersection;

class Sphere {
	public:
	  	Vector center; 
	  	float radius;

		Sphere();
		Sphere(Vector, float);
		bool intersect(Ray&, float*, Intersection*);
		bool intersectP(Ray&);

};

#endif