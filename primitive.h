#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class Intersection;

class Primitive {
  public:
	  virtual ~Primitive();
	  virtual bool intersect(Ray& ray, float* thit, Intersection* in);
	  virtual bool intersectP(Ray& ray);
};

class Sphere : public Primitive {
	public:
	  	Vector center; 
	  	float radius;

		Sphere();
		Sphere(Vector, float);
		bool intersect(Ray&, float*, Intersection*);
		bool intersectP(Ray&);

};

#endif