#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h"
#include "ray.h"

using namespace std;

class Sphere {
	public:
	  	Vector center; 
	  	int radius;

		Sphere();
		Sphere(Vector, int);
		bool intersect(Ray&);
};

#endif