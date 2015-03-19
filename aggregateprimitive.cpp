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
	Intersection inter;
	for(int i = 0; i < list_primitives.size(); i++) {
		Primitive* shape = list_primitives[i];

		if(shape->intersect(ray, &current_hit, &inter)) {
			//cout << "current_hit: " << current_hit << " min_hit: " << min_hit << endl;
			if(current_hit < min_hit) {
				min_hit = current_hit;
				*in = inter;
				//in->primitive = shape; // set the primitive it hits to the current shape if it's the current mins
			}
			intersected = true;
		}
	}
	*thit = min_hit;
	return intersected;
}

bool AggregatePrimitive::intersectP(Ray& ray, Primitive* currShape) {
	bool intersected = false;
	//cout << "Intersect ray: "; ray.print(); cout << endl;
	for(int i = 0; i < list_primitives.size(); i++) {
		Primitive* shape = list_primitives[i];

		if(shape != currShape && shape->intersectP(ray)) {
			//cout << "intersection happened." << endl;
			intersected = true;
		}
	}
	return intersected;
}