#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include <iostream>
#include <cmath>
#include <vector>
#include "sphere.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class AggregatePrimitive {
  public:
	  vector<Sphere*> list_primitives;

	  AggregatePrimitive(vector<Sphere*> list);
	  bool intersect(Ray& ray, float* thit, Intersection* in);
};

#endif