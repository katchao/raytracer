#ifndef RAY_H
#define RAY_H

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

//class Vector;

class Ray {
  public:
	  Vector start;
	  Vector dir; // start - position on viewport
	  float t_min, t_max;

	  Ray();
	  Ray(Vector, Vector);
	  void print();
};

#endif