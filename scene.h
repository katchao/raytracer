#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "sampler.h"
#include "sample.h"
#include "film.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "raytracer.h"
#include "light.h"
#include "primitive.h"
#include "aggregateprimitive.h"
#include <vector>
#include "objparser.h"

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
	vector<Primitive*> primitives;

	Scene(Vector, int, int);

    void render();
};

#endif