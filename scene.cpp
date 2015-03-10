#include "scene.h"
#include "vector.h"
#include "film.h"
#include "ray.h"
#include "camera.h"
#include <vector>

Scene::Scene(Vector eye, int x, int y) {
	eye_position = eye;
	dim_x = x;
	dim_y = y;
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
	Vector color = Vector(0, 0, 0);
	Film film = Film(dim_x, dim_y);
	Camera camera = Camera(eye_position);
	Sphere sphere = Sphere(Vector(0,0,0), 5);
	
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		film.storeSamples(color, sample.x, sample.y);
	}
	film.writeImage();
}

int main() {
	Scene scene = Scene(Vector(), 100, 100);
	scene.render();

	//want to print out the size of the buckets
	return 0;
}