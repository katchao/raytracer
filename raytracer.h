#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"

using namespace std;

class Raytracer {
  public:
	  vector<Sphere> list_primitives;
	  Raytracer();
	  void trace(Ray&, int, Color*);
};

#endif