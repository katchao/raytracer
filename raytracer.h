#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "color.h"

using namespace std;

class Raytracer {
  public:
	  Raytracer();
	  void trace(Ray&, int, Color*);
};

#endif