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
	  Camera();
	  void generateRay(Sample& sample, Ray* ray);
};

#endif