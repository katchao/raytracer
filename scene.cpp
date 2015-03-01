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

void render() {
}