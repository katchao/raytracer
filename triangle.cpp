#include "triangle.h"

Triangle::Triangle() {
}

Triangle::Triangle(Vector iv1, Vector iv2, Vector iv3) {
	v1 = iv1;
	v2 = iv2;
	v3 = iv3;
	//type = true;
}

bool Triangle::intersect(Ray &ray, float* thit, Intersection* in) {
	float xa = v1.x; float ya = v1.y; float za = v1.z;
	float xb = v2.x; float yb = v2.y; float zb = v2.z;
	float xc = v3.x; float yc = v3.y; float zc = v3.z;
	float xd = ray.dir.x; float yd = ray.dir.y; float zd = ray.dir.z;
	float xe = ray.start.x; float ye = ray.start.y; float ze = ray.start.z;

	float a = xa - xb; float b = ya - yb; float c = za - zb;
	float d = xa - xc; float e = ya - yc; float f = za - zc;
	float g = xd; float h = yd; float i = zd;
	float j = xa - xe; float k = ya - ye; float l = za - ze;

	float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	float t = ((f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M) * -1;
	cout << "thit: " << t;
	cout << "ray.t_min: " << ray.t_min;
	cout << "ray.t_max: " << ray.t_max;
	if(t < ray.t_min || t > ray.t_max) { return false; }

	float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if(gamma < 0 || gamma > 1) { return false; }

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if(beta < 0 || beta > (1-gamma)) { return false; }

	*thit = t;
	

	// currPos = e + thit *d
	Vector currPos = Vector();
	Vector prod = Vector(); prod.scalar_multiply(ray.dir, *thit);
	currPos.add(ray.start, prod);

	// normal = cross(v2 - v1, v3 - v1);
	Vector normal = Vector();
	Vector V = Vector(); V.subtract(v2, v1);
	Vector W = Vector(); W.subtract(v3, v1);

	normal.x = (V.y * W.z) - (V.z * W.y);
	normal.y = (V.z * W.x) - (V.x * W.z);
	normal.z = (V.x * W.y) - (V.y * W.x);
	normal.normalize();

	LocalGeo local = LocalGeo(currPos, normal);
	*in = Intersection(local, this);
	return true;
}

bool Triangle::intersectP(Ray &ray) {
	float xa = v1.x; float ya = v1.y; float za = v1.z;
	float xb = v2.x; float yb = v2.y; float zb = v2.z;
	float xc = v3.x; float yc = v3.y; float zc = v3.z;
	float xd = ray.dir.x; float yd = ray.dir.y; float zd = ray.dir.z;
	float xe = ray.start.x; float ye = ray.start.y; float ze = ray.start.z;

	float a = xa - xb; float b = ya - yb; float c = za - zb;
	float d = xa - xc; float e = ya - yc; float f = za - zc;
	float g = xd; float h = yd; float i = zd;
	float j = xa - xe; float k = ya - ye; float l = za - ze;

	float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);

	float t = ((f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M) * -1;
	if(t < ray.t_min || t > ray.t_max) { return false; }

	float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if(gamma < 0 || gamma > 1) { return false; }

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if(beta < 0 || beta > (1-gamma)) { return false; }

	if(t < 0.004) { // shadow bias
		return false;
	}

	return true;
}