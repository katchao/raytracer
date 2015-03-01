#include "scene.h"

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

	while (sampler.getSample(&sample)) {
	}
}

int main() {
	Scene scene = Scene(Vector(), 2, 2);
	scene.render();
	return 0;
}