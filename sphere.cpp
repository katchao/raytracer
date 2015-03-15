#include "sphere.h"

Sphere::Sphere() {
	radius = 0;
	center = Vector(0, 0, 0);
}

Sphere::Sphere(Vector icenter, float iradius) {
	center = icenter;
	radius = iradius;
}

bool Sphere::intersect(Ray &ray, float* thit, Intersection* in) {
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
	*thit = min(t1, t2);

	// build localGeo
	// currPos = e + thit *d
	Vector currPos = Vector();
	Vector prod = Vector(); prod.scalar_multiply(d, *thit);
	currPos.add(e, prod);
	// normal = 2(p - c)/R
	Vector normal = Vector();
	normal.subtract(currPos, c);
	//normal.scalar_multiply(normal, 2.0f);
	normal.scalar_divide(normal, r);

	LocalGeo local = LocalGeo(currPos, normal);
	*in = Intersection(local, this);
	return true;
}

bool Sphere::intersectP(Ray &ray) {
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

	float min_t;
	float det = sqrt(discriminant);
	Vector minus_d = Vector();
	minus_d.scalar_multiply(d, -1.0);
	float t1 = (minus_d.dot_product(e_c) + det)/d_dot_d;
	float t2 = (minus_d.dot_product(e_c) - det)/d_dot_d;
	
	// get the smallest thit value
	min_t = min(t1, t1);
	
	if(min_t < 0.004) { // shadow bias
		return false;
	}
	return true;
}

