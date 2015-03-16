#include "camera.h"

// Main function: generate rays

Camera::Camera(Vector ieye, Vector ul, Vector ur, Vector ll, Vector lr, int boundx, int boundy) {
	eye = ieye; 
	UL = ul; UR = ur; LL = ll; LR = lr;
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
	add1.scalar_multiply(add1, u);

	Vector prod3 = Vector(); prod3.scalar_multiply(LR, v);
	Vector prod4 = Vector(); prod4.scalar_multiply(UR, (1-v));
	Vector add2 = Vector(); add2.add(prod3, prod4); // <(1, 0, -2>
	add2.scalar_multiply(add2, (1.0f-u));

	P.add(add1, add2);

	Vector direction = Vector(); direction.subtract(P, eye); // <0, 0, -2>

	*ray = Ray(eye, direction);
}
