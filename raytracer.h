#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"
#include "BRDF.h"
#include "light.h"

using namespace std;

class Raytracer {
  public:
	  vector<Sphere> list_primitives;
	  vector<Light> list_lights;

	  Raytracer();
	  void trace(Ray&, int, Color*);
	  Color shading(LocalGeo&, BRDF&, Ray&, Color&, Light&);
};

#endif