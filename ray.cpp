#include "ray.h"

Ray::Ray() {
	pos = Vector();
	dir = Vector();
	t_min = 0;
	t_max = 1;
}
