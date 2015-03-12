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
	/* s = e + us*U + vs*V +ws*W */ 
	s.add(eye, newU); s.add(s, newV); s.add(s, w);
	direction.subtract(s, eye);

	//R(t) = E+t(P-E)
	// int z = -2;//should always point to viewer
	// Vector direction = Vector();
	// direction.subtract(Vector(sample.x, sample.y, z), eye);
	//cout << "My direction: ( " << direction.x << "," << direction.y << "," << direction.z << ")\n";
	*ray = Ray(eye, direction);
}
