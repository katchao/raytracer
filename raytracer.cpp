#include "raytracer.h"

Raytracer::Raytracer() {
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	Sphere sphere = list_primitives[0];
	bool has_intersected = sphere.intersect(ray);
	if ((has_intersected) && (depth < 5000)){
		*color = Color(1.0f, 0.0f, 0.0f);
	} else if ((has_intersected) && (depth > 5000)){
		*color = Color(0.0f, 1.0f, 0.0f);
	} else {
		*color = Color(0.0f, 0.0f, 0.0f);
	}

}
