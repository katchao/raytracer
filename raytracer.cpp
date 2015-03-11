#include "raytracer.h"

Raytracer::Raytracer() {
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	Sphere sphere = list_primitives[0];
	bool has_intersected = sphere.intersect(ray);
	if(has_intersected) {
		*color = Color(1.0f, 0.0f, 0.0f);
	}
	else {
		*color = Color(0.0f, 0.0f, 0.0f);
	}
	//cout << "Has_intersected: " << has_intersected;
	//cout << " Ray Start: <" << ray.start.x << ", " << ray.start.y << ", " << ray.start.z << ">";
	//cout << " Ray Dir: <" << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << ">";
}