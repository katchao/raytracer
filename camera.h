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
	  Vector eye; //eye position
	  Vector p; //sample.x, sample.y
	  Camera(Vector);
	  void generateRay(Sample& sample, Ray* ray);
};

#endif