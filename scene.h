#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "sampler.h"
#include "sample.h"

using namespace std;

class Scene {
  public:
	Vector eye_position;
	/* for corners of image */
	Vector UL;
	Vector LL;
	Vector UR;
	Vector LR;
	int dim_x, dim_y;

	Scene(Vector, int, int);

    void render();
};

#endif