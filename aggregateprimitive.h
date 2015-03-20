#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>
#include "primitive.h"
#include "ray.h"
#include "intersection.h"
#include "transformation.h"

using namespace std;

class AggregatePrimitive {
  public:
	  vector<Primitive*> list_primitives;
	  vector<Transformation*> list_transformations;

	  AggregatePrimitive();
	  AggregatePrimitive(vector<Primitive*> list);//, vector<Transformation*> trans);
	 // bool intersect(Ray& ray, float* thit, Intersection* in, vector<Transformation*> trans);
	  bool intersect(Ray& ray, float* thit, Intersection* in);
	  bool intersectE(Ray& ray, float* thit, Intersection* in, Transformation& trans);
	  bool intersectP(Ray& ray, Primitive*);
};

#endif