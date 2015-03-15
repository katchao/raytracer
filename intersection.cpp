#include "intersection.h"

Intersection::Intersection() {
}

Intersection::Intersection(LocalGeo ilocal, Sphere* isphere) {
	local = ilocal;
	sphere = isphere;
}