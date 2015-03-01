#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

class Scene {
  public:
	Vector eye_position;
	int dim_x, dim_y;

	Scene();
	Scene(Vector, int, int);

    void render();
};

#endif