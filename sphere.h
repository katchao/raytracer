#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class Intersection;

class Sphere {
	public:
	  	Vector center; 
	  	int radius;

		Sphere();
		Sphere(Vector, int);
		bool intersect(Ray&, float*, Intersection*);

};

#endif