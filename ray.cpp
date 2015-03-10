#include "ray.h"

Ray::Ray() {
	start = Vector(0, 0, 0);
	dir = Vector(0, 0, 0);
	t_min = 0;
	t_max = 1;
}

Ray::Ray(Vector ipos, Vector idir) {
	start = ipos;
	dir = idir;
	t_min = 0;
	t_max = 1;
}