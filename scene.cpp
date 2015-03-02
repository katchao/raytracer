#include "scene.h"
#include "vector.h"
#include "film.h"
#include <vector>

Scene::Scene() {
	eye_position = Vector();
	dim_x = 0;
	dim_y = 0;
}

Scene::Scene(Vector eye, int x, int y) {
	eye_position = eye;
	dim_x = x;
	dim_y = y;
}

void Scene::render() {
	Sampler sampler = Sampler(dim_x, dim_y);
	Sample sample = Sample();
	Vector color = Vector(0, 0, 0);
	Film film = Film(dim_x, dim_y);
	
	while (sampler.getSample(&sample)) {
		film.storeSamples(color, sample.x, sample.y);
	}
	//
	film.writeImage();
}

int main() {
	Scene scene = Scene(Vector(), 2, 2);
	scene.render();

	//want to print out the size of the buckets
	return 0;
}