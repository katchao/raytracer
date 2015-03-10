#include "sphere.h"

Sphere::Sphere() {
	radius = 0;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(Vector icenter, int iradius) {
	center = icenter;
	radius = iradius;
}

bool Sphere::intersect(Ray &ray) {
	Vector e = ray.start;
	Vector c = center;
	Vector d = ray.dir;
	int r = radius;

	Vector e_c = Vector();
	e_c.subtract(e, c);
	float d_dot_d = d.dot_product(d);

	float det = sqrt( pow(d.dot_product(e_c), 2) - d_dot_d * (e_c.dot_product(e_c) - pow(r,2)));
	Vector minus_d = Vector();
	minus_d.scalar_multiply(d, -1.0);
	float t1 = (minus_d.dot_product(e_c) + det)/d_dot_d;
	float t2 = (minus_d.dot_product(e_c) - det)/d_dot_d;

	if(t1 > ray.t_max || t2 > ray.t_max || t1 < ray.t_min || t2 < ray.t_min) {
		return false;
	}
	else {
		return true;
	}
}