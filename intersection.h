#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <cmath>
#include "localgeo.h"
#include "primitive.h"

using namespace std;
class Primitive;

class Intersection {
  public:
	  LocalGeo local;
      Primitive* primitive;

	  Intersection();
	  Intersection(LocalGeo, Primitive*);
};

#endif