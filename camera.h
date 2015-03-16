#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "sample.h"
#include "ray.h"

using namespace std;


class Camera {
  public:
	  Vector eye, UL, UR, LL, LR; //eye position
	  int nx, ny;
	  Camera(Vector, Vector, Vector, Vector, Vector, int, int);
	  void generateRay(Sample& sample, Ray* ray);
};

#endif