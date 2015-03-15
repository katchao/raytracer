#include "scene.h"

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

	Raytracer raytracer = Raytracer(eye_position);

	//objects
	Sphere sphere = Sphere(Vector(0.0f, 0.0f, -2.0f), 1.0f); raytracer.list_primitives.push_back(sphere);
	Sphere sphere2 = Sphere(Vector(0.5f, 0.5f, -1.2f), 0.3f); raytracer.list_primitives.push_back(sphere2);

	//lights
	PointLight pl1 = PointLight(Vector(2, 2, 2), Color(1.0f, 0.0f, 0.0f));
	PointLight pl2 = PointLight(Vector(-2, 2, 2), Color(0.0f, 1.0f, 0.0f));
	PointLight pl3 = PointLight(Vector(0, -2, 2), Color(0.0f, 0.0f, 1.0f));
	raytracer.list_lights.push_back(pl1);
	raytracer.list_lights.push_back(pl2);
	raytracer.list_lights.push_back(pl3);

	int counter = 0;
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, counter, &color);
		film.storeSamples(color, sample);
		counter++;
	}
	cout << "Computing Complete.\n";
	film.writeImage();
	cout << "Rendering Complete.\n";
}

int main() {
	Scene scene = Scene(Vector(0.0f, 0.0f, 0.0f), 100, 100);
	scene.render();

	//want to print out the size of the buckets
	return 0;
}