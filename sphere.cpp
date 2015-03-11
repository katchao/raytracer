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
	float r = radius;

	Vector e_c = Vector();
	e_c.subtract(e, c);
	float d_dot_d = d.dot_product(d);
	//cout << "d dot e-c = " << d.dot_product(e_c) << "\n"; 
	float first_part = pow(d.dot_product(e_c), 2);
	//cout << "first part = " << first_part << "\n";
	float second_part = d_dot_d * (e_c.dot_product(e_c) - pow(r,2));
	//cout << "second_part = " << second_part << "\n";
	float discriminant = first_part - second_part;
	//cout << "discriminant = " << discriminant << "\n";
	if (discriminant < 0) { // the ray doesn't intersect the polygon (imaginary number)
		return false;
	} else {
		float det = sqrt(discriminant);
		//cout << "det not less than zero";

		//cout << "det = " << det << "\n";

		Vector minus_d = Vector();
		minus_d.scalar_multiply(d, -1.0);
		float t1 = (minus_d.dot_product(e_c) + det)/d_dot_d;
		float t2 = (minus_d.dot_product(e_c) - det)/d_dot_d;

		// if(t1 > ray.t_max || t2 > ray.t_max || t1 < ray.t_min || t2 < ray.t_min) {
		// 	return false;
		// }
		// else {
			return true;
		//}

	}

}