#include "aggregateprimitive.h"

AggregatePrimitive::AggregatePrimitive() {
}


AggregatePrimitive::AggregatePrimitive(vector<Primitive*> ilist) {
	list_primitives = ilist;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in) {
	float current_hit;
	float min_hit = INFINITY;
	bool intersected = false;
	for(int i = 0; i < list_primitives.size(); i++) {
		Primitive* shape = list_primitives[i];

		if(shape->intersect(ray, &current_hit, in)) {
			if(current_hit < min_hit) {
				current_hit = min_hit;
				in->primitive = shape; // set the primitive it hits to the current shape if it's the current min
			}
			intersected = true;
		}
	}
	*thit = min_hit;
	return intersected;
}

bool AggregatePrimitive::intersectP(Ray& ray) {
	bool intersected = false;
	for(int i = 0; i < list_primitives.size(); i++) {
		Primitive* shape = list_primitives[i];

		if(shape->intersectP(ray)) {
			intersected = true;
		}
	}
	return intersected;
}