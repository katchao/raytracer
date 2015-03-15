#include "intersection.h"

Intersection::Intersection() {
}

Intersection::Intersection(LocalGeo ilocal, Primitive* iprimitive) {
	local = ilocal;
	//primitive = iprimitive;
}


Intersection::Intersection(LocalGeo ilocal, Triangle* iprimitive) {
	local = ilocal;
	primitive = iprimitive;
}