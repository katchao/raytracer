#include "localgeo.h"

// Every object has its own BRDF class

LocalGeo::LocalGeo() {
}

LocalGeo::LocalGeo(Vector ipos, Vector inormal) {
	pos = ipos;
	normal = inormal;

	normal.normalize();
}