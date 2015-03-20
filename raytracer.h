#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "primitive.h"
#include "BRDF.h"
#include "light.h"
#include "intersection.h"
#include "aggregateprimitive.h"
#include "transformation.h"

using namespace std;

class Raytracer {
  public:
	  vector<Primitive*> list_primitives;
	  vector<Light*> list_lights;
	  vector<Transformation*> list_transformations;
	  Vector eye;
	  AmbientLight* amb;
	  int number_of_transformations;

	  Raytracer(Vector);
	  void trace(Ray&, int, Color*);
	  Color shading(LocalGeo&, BRDF&, Ray&, Color&, Light&);
};

#endif