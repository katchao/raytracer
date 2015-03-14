#include "raytracer.h"

Raytracer::Raytracer() {
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	Sphere sphere = list_primitives[0];
	float thit;
	bool has_intersected = sphere.intersect(ray, &thit);

	// miss
	if(!has_intersected) {
		*color = Color(0.0f, 0.0f, 0.0f);
		return;
	}

	cout << thit;
	*color = Color(1.0f, 0.0f, 0.0f);

}


// shoot a ray from your eye to the object
// from the intersection, shoot another ray from the intersection to light
// if it hits another object, don't shade it (because that point's being blocked)
// if it hits the light, use phong shading model