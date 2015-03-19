#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <iostream>
#include <cmath>
#include <vector>
#include "matrix.h"
#include "vector.h"

using namespace std;

//Support Point, Vector, Normal, Ray, LocalGeo transformation by operator * overloading
class Transformation {
  public:
	  Matrix m;
	  Matrix minvt; //the inverse transpose of M

	  Transformation();
	  Transformation(Matrix);

	  Vector transform(Vector);
	  //void print();
};

#endif