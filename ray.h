#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

//class Vector;

class Ray {
  public:
	  Vector pos;
	  Vector dir;
	  float t_min, t_max;

	  Ray();
};

#endif