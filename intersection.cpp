#include "intersection.h"

Intersection::Intersection() {
}

Intersection::Intersection(LocalGeo ilocal, Sphere* iprimitive) {
	local = ilocal;
	primitive = iprimitive;
}