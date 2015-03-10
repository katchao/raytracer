#include "camera.h"

// Main function: generate rays

Camera::Camera(Vector ieye) {
	eye = ieye;
}


/* Create a ray starting from the camera that passes through the
   corresponding pixel (sample.x, sample.y) on the image plane. */
void Camera::generateRay(Sample& sample, Ray* ray) {
	//R(t) = E+t(P-E)
	int x = sample.x;
	int y = sample.y;
	int z = 0;
	Vector direction = Vector();
	direction.subtract(Vector(sample.x, sample.y, z), eye);
	*ray = Ray(eye, direction);
}