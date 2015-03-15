#include "aggregateprimitive.h"

AggregatePrimitive::AggregatePrimitive(vector<Sphere*> ilist) {
	list_primitives = ilist;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in) {
	for(int i = 0; i < list_primitives.size(); i++) {
		Sphere* shape = list_primitives[i];
		shape->intersect(ray, thit, in);
	}
}