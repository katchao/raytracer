#include "sphere.h"

Sphere::Sphere() {
	radius = 0;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(Vector icenter, int iradius) {
	center = icenter;
	radius = iradius;
}

bool Sphere::intersect(Ray &ray, float* thit) {
	Vector e = ray.start;
	Vector c = center;
	Vector d = ray.dir;
	float r = radius;

	Vector e_c = Vector();
	e_c.subtract(e, c);
	float d_dot_d = d.dot_product(d);
	float discriminant = pow(d.dot_product(e_c), 2) - (d_dot_d * (e_c.dot_product(e_c) - pow(r,2)));
	if (discriminant < 0) { // the ray doesn't intersect the polygon (imaginary number)
		return false;
	}
	float det = sqrt(discriminant);
	Vector minus_d = Vector();
	minus_d.scalar_multiply(d, -1.0);
	float t1 = (minus_d.dot_product(e_c) + det)/d_dot_d;
	float t2 = (minus_d.dot_product(e_c) - det)/d_dot_d;

	*thit = t1;
	return true;
	/* This doen't work at the moment...*/
		/*
		if(t1 > ray.t_max || t2 > ray.t_max || t1 < ray.t_min || t2 < ray.t_min) {
		 	return false;
		}*/
		// else {
		// 	return true;
		// }


}
