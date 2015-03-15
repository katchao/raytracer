#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include <iostream>
#include <cmath>
#include <vector>
#include "primitive.h"
#include "ray.h"
#include "intersection.h"

using namespace std;

class AggregatePrimitive {
  public:
	  vector<Primitive*> list_primitives;

	  AggregatePrimitive();
	  AggregatePrimitive(vector<Primitive*> list);
	  bool intersect(Ray& ray, float* thit, Intersection* in);
	  bool intersectP(Ray& ray);
};

#endif