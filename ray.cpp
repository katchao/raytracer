#include "ray.h"

Ray::Ray() {
	start = Vector(0, 0, 0);
	dir = Vector(0, 0, 0);
	t_min = 0.0f;
	t_max = 100.0f;
}

Ray::Ray(Vector ipos, Vector idir) {
	start = ipos;
	dir = idir;
	t_min = 0.0f;
	t_max = 100.0f;
}

void Ray::print() {
	cout << "Ray start: "; start.print(); cout << " dir: "; dir.print();
}