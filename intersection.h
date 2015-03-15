#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <cmath>
#include "localgeo.h"
#include "sphere.h"

using namespace std;
class Sphere;

class Intersection {
  public:
	  LocalGeo local;
      Sphere* sphere;

	  Intersection();
	  Intersection(LocalGeo, Sphere*);
};

#endif