#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class Primitive {
  public:
	  virtual bool intersect(Ray& ray, float* thit, Intersection* in);
	  virtual bool intersectP(Ray& ray);
};

#endif