#include "camera.h"

// Main function: generate rays

Camera::Camera(Vector ieye, Vector ul, Vector ur, Vector ll, Vector lr, int boundx, int boundy) {
	eye = ieye; 
	UL = ul; UR = ur; LL = ll; LR = lr;
	l = UL.x; 
	r = UR.x; 
	top = UL.y; 
	bottom = LL.y;
	//this is the z coordinate for the near clipping plane
	n = UL.z;
	//Pixels in the x direction
	nx = boundx;
	//Pixels in the y direction
	ny = boundy;
}


/* Create a ray starting from the camera that passes through the
   corresponding pixel (sample.x, sample.y) on the image plane. */
void Camera::generateRay(Sample& sample, Ray* ray) {
	/* P = u (vLL+ (1-v)UL)+ (1-u)(vLR+ (1-v)UR) */
	/* R(t) = E+t(P-E) */
	float v = sample.y/ny;
	float u = sample.x/nx;

	Vector P = Vector();
	Vector prod1 = Vector(); prod1.scalar_multiply(LL, v);
	Vector prod2 = Vector(); prod2.scalar_multiply(UL, (1-v));
	Vector add1 = Vector(); add1.add(prod1, prod2); // <(-1, 0, -2)>
	//cout << "add1: " << add1.x << " " << add1.y << " " << add1.z << endl;
	add1.scalar_multiply(add1, u);
	//cout << "add1: " << add1.x << " " << add1.y << " " << add1.z << endl;

	Vector prod3 = Vector(); prod3.scalar_multiply(LR, v);
	Vector prod4 = Vector(); prod4.scalar_multiply(UR, (1-v));
	Vector add2 = Vector(); add2.add(prod3, prod4); // <(1, 0, -2>
	//cout << "add2: " << add2.x << " " << add2.y << " " << add2.z << endl;
	add2.scalar_multiply(add2, (1.0f-u));

	P.add(add1, add2);
	//cout << "v: " << v << " u: " << u << endl;
	//cout << "UL: " << UL.x << UL.y << UL.z << " UR: " << UR.x << UR.y << UR.z << endl;
	//cout << "LL: " << LL.x << LL.y << LL.z << " LR: " << LR.x << LR.y << LR.z << endl; // <-1, 0, -2>

	Vector direction = Vector(); direction.subtract(P, eye);

	//cout << "eye: " << eye.x << " " << eye.y << " " << eye.z << endl;
	//cout << "P: " << P.x << " " << P.y << " " << P.z << endl;
	//cout << "direction: " << direction.x << " " << direction.y << " " << direction.z << endl; // <0, 0, -2>

	*ray = Ray(eye, direction);
	/*
	Vector u = Vector(1, 0, 0);
	Vector v = Vector(0, 1, 0);
	Vector w = Vector(0, 0, -1);
	float x = sample.x;
	float y = sample.y;
	float us = l + (r - l) * (x/nx);
	//cout << "us :" << us << "\n";
	float vs = bottom + (top - bottom) * (y/ny);
	Vector newU = Vector();
	Vector newV = Vector();
	Vector s = Vector();
	Vector direction = Vector();

	newU.scalar_multiply(u, us);
	newV.scalar_multiply(v, vs);
	s.add(eye, newU); s.add(s, newV); s.add(s, w);
	direction.subtract(s, eye);

	//R(t) = E+t(P-E)
	// int z = -2;//should always point to viewer
	// Vector direction = Vector();
	// direction.subtract(Vector(sample.x, sample.y, z), eye);
	//cout << "My direction: ( " << direction.x << "," << direction.y << "," << direction.z << ")\n";
	*ray = Ray(eye, direction);*/
}
