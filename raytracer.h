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

using namespace std;

class Raytracer {
  public:
	  vector<Primitive*> list_primitives;
	  vector<Light*> list_lights;
	  Vector eye;
	  AmbientLight* amb;

	  Raytracer(Vector);
	  void trace(Ray&, int, Color*);
	  Color shading(LocalGeo&, BRDF&, Ray&, Color&, Light&);
};

#endif