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
			if(current_hit < min_hit) {
				min_hit = current_hit;
				*in = inter;
			}
			intersected = true;
		}
	}
	*thit = min_hit;
	return intersected;
}

bool AggregatePrimitive::intersectP(Ray& ray, Primitive* currShape) {
	bool intersected = false;
	//cout << "lray1: "; ray.print(); cout << endl;
	for(int i = 0; i < list_primitives.size(); i++) {
		Primitive* shape = list_primitives[i];

		if(shape != currShape && shape->intersectP(ray)) {
			//cout << "lray2: "; ray.print(); cout << endl; cout << "currShape: "; currShape->print(); cout << "intersected shape: "; shape->print();
			intersected = true;
		}
	}
	//cout << "-----------------------------" << endl;
	return intersected;
}