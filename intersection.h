#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <cmath>
#include "localgeo.h"
#include "primitive.h"
#include "triangle.h"

using namespace std;
//class Primitive;
class Triangle;

class Intersection {
  public:
	  LocalGeo local;
      //Primitive* primitive;
	  Triangle* primitive;

	  Intersection();
	  //Intersection(LocalGeo, Primitive*);
	  Intersection(LocalGeo, Triangle*);
};

#endif