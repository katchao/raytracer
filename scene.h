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
#include "material.h"
#include "BRDF.h"
#include "material.h"
#include <vector>
#include "objparser.h"
#include "transformation.h"

using namespace std;

class Scene {
  public:
	Vector eye;
	Camera camera;

	/* for corners of image */
	Vector UL;
	Vector LL;
	Vector UR;
	Vector LR;
	int dim_x, dim_y, number_of_transformations;
	vector<Primitive*> list_primitives;
	vector<Light*> list_lights;
	vector<Material*> list_materials;
	vector<Transformation*> list_transformations;
	string file;

	Scene();
	Scene(int, int);

    void render();
	void parse_input(const char* input_file, bool&);
};

#endif