#include "intersection.h"

Intersection::Intersection() {
}

Intersection::Intersection(LocalGeo ilocal, Primitive* iprimitive) {
	local = ilocal;
	primitive = iprimitive;
}