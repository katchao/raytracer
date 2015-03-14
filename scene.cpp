#include "scene.h"
#include "vector.h"
#include "film.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "sphere.h"
#include "raytracer.h"
#include <vector>

Scene::Scene(Vector eye, int x, int y) {
	eye_position = eye;
	dim_x = x;
	dim_y = y;
	//dim_z = z;
	UL = Vector(-1,  1, -1);
	UR = Vector( 1,  1, -1);
	LR = Vector( 1, -1, -1);
	LL = Vector(-1, -1, -1);
}

/*
void render() {
            while (!sampler.generateSample(&sample) {
                        camera.generateRay(sample, &ray);
                        raytracer.trace(ray, &color);
                        film.commit(sample, color);
            }
            film.writeImage();
}
*/

void Scene::render() {
	Sampler sampler = Sampler(dim_x, dim_y);
	Sample sample = Sample();
	Ray ray = Ray();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Film film = Film(dim_x, dim_y);
	Camera camera = Camera(eye_position, UL, UR, LL, LR, dim_x, dim_y);

	Raytracer raytracer = Raytracer();
	Sphere sphere = Sphere(Vector(0,0,-2), 1);

	raytracer.list_primitives.push_back(sphere);
	int counter = 0;
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, counter, &color);
		film.storeSamples(color, sample);
		counter++;
		//cout << "My Color Scene (" << color.r << "," << color.g << "," << color.b  << ") at (" << sample.x << ", " << sample.y << ")\n";
	}
	cout << "Computing Complete.\n";
	film.writeImage();
	cout << "Rendering Complete.\n";
}

int main() {
	Scene scene = Scene(Vector(0, 0, 0), 200, 100);
	scene.render();

	//want to print out the size of the buckets
	return 0;
}
