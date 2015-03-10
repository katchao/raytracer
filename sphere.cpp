#include "sphere.h"

Sphere::Sphere() {
	radius = 0;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(Vector icenter, int iradius) {
	center = icenter;
	radius = iradius;
}

