#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

class Raytracer {
  public:
	  void trace(Ray&, int, Vector);
};

#endif