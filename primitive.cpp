#include "primitive.h"

Primitive::~Primitive() {
}


bool Primitive::intersect(Ray& ray, float* thit, Intersection* in) {
}

bool Primitive::intersectP(Ray& ray) {
	cout << "test";
}

bool Primitive::intersectE(Ray& ray, float* thit, Intersection* in, Transformation& trans) {

}

void Primitive::print() {
}

/************************************************/
// Sphere ////////////////////////////////////////
/************************************************/


Sphere::Sphere() : Primitive() {
	radius = 0;
	center = Vector(0, 0, 0);
	type = 0;
}

Sphere::Sphere(Vector icenter, float iradius) : Primitive() {
	center = icenter;
	radius = iradius;
}

Sphere::Sphere(Vector icenter, float iradius, Material* imat) : Primitive() {
	center = icenter;
	radius = iradius;
	mat = imat;
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

	if(*thit < 0.00004) { // shadow bias
		return false;
	}

	if(*thit < ray.t_min || *thit > ray.t_max) {
		return false;
	}

	// build localGeo
	Vector currPos = e + d * (*thit);
	// normal = 2(p - c) or (p-c)/r
	Vector normal = (currPos - c)/r;

	LocalGeo local = LocalGeo(currPos, normal);
	*in = Intersection(local, this);
	return true;
}

bool Sphere::intersectE(Ray &ray, float* thit, Intersection* in, Transformation& trans) {
	Ray transRay = Ray();
	cout << "original ray direction = "; ray.dir.print(); cout << endl;
	cout << "original ray start = "; ray.start.print(); cout << endl;
	
	transRay.dir = trans.transform_dir(ray.dir);
	cout << "\ntransRay dir   = "; transRay.dir.print(); cout << endl;
	transRay.start = trans.transform_pos(ray.start); cout << endl;
	cout << "transRay.start  =  "; transRay.start.print();

// intersection with the new Transformed Ray

	Vector e = transRay.start;
	Vector c = center;
	Vector d = transRay.dir;
	float r = radius;

	Vector e_c = Vector();
	e_c.subtract(e, c);
	float d_dot_d = d.dot_product(d);
	float discriminant = pow(d.dot_product(e_c), 2) - (d_dot_d * (e_c.dot_product(e_c) - pow(r,2)));
	cout << " can find the Discriminant :" << discriminant << " \n";
	if (discriminant < 0) { // the ray doesn't intersect the polygon (imaginary number)
	cout << "I am false?\n";
		return false;

	}
	float det = sqrt(discriminant);
	Vector minus_d = Vector();
	minus_d.scalar_multiply(d, -1.0);
	float t1 = (minus_d.dot_product(e_c) + det)/d_dot_d;
	float t2 = (minus_d.dot_product(e_c) - det)/d_dot_d;
	cout << "Before Segfault";
	// get the smallest thit value
	*thit = min(t1, t2);

	if(*thit < 0.00004) { // shadow bias
		return false;
	}

	if(*thit < ray.t_min || *thit > ray.t_max) {
		return false;
	}

	// Build Local Geo with the old ray
	Vector orig_e = ray.start;
	Vector orig_d = ray.dir; 
	Vector currPos = orig_e + orig_d * (*thit);
	//THE NORMAL MUST CHANGE
	// normal = 2(p - c) or (p-c)/r
	Vector normal = trans.transform_normal((currPos - c)/r);


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
	min_t = min(t1, t2);

	if(min_t < 0.004) { // shadow bias
		return false;
	}

	if(min_t < ray.t_min || min_t > ray.t_max) {
		return false;
	}
	return true;
}

void Sphere::print() {
	cout << "Sphere Center: "; center.print(); cout << " Radius: " << radius << "  Material: "; mat->print(); cout << endl;
}


/**************************************************/
// Triangle ////////////////////////////////////////
/**************************************************/

Triangle::Triangle() : Primitive() {
}

Triangle::Triangle(Vector iv1, Vector iv2, Vector iv3) : Primitive() {
	v1 = iv1;
	v2 = iv2;
	v3 = iv3;
	type = 1;
}

Triangle::Triangle(Vector iv1, Vector iv2, Vector iv3, Material* imat) : Primitive() {
	v1 = iv1;
	v2 = iv2;
	v3 = iv3;
	type = 1;
	mat = imat;
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
	if(t < ray.t_min || t > ray.t_max) { return false; }

	float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if(gamma < 0 || gamma > 1) { return false; }

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if(beta < 0 || beta > (1-gamma)) { return false; }

	*thit = t;
	
	if(t < 0.00004) { // shadow bias
		return false;
	}
	// currPos = e + thit *d
	Vector currPos = Vector();
	Vector prod = Vector(); prod.scalar_multiply(ray.dir, *thit);
	currPos.add(ray.start, prod);

	
	// normal = cross(v2 - v1, v3 - v1);
	Vector normal = Vector();
	Vector V = v2 - v1;
	Vector W = v3 - v1;

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

	if(t < 0.00004) { // shadow bias
		return false;
	}

	return true;
}

void Triangle::print() {
	cout << "Triangle v1: "; v1.print(); cout << " v2: "; v2.print(); cout << " v3: "; v3.print(); cout << endl;
}