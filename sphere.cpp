#include "sphere.h"

Sphere::Sphere() {
	radius = 0;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(Vector icenter, int iradius) {
	center = icenter;
	radius = iradius;
}

bool Sphere::intersect(Ray &ray, float* thit, LocalGeo* local) {
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
	
	// get the smallest thit value
	if(t1 < t2) {
		*thit = t1;
	}
	else {
		*thit = t2;
	}

	// build localGeo
	// currPos = e + thit *d
	Vector currPos = Vector();
	Vector prod = Vector(); prod.scalar_multiply(d, *thit);
	currPos.add(e, prod);
	// normal = 2(p - c)/R
	Vector normal = Vector();
	normal.subtract(currPos, c);
	normal.scalar_multiply(normal, 2.0f);
	//normal.scalar_divide(normal, r);

	*local = LocalGeo(currPos, normal);
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
