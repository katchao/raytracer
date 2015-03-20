#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
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

	  Vector transform_dir(Vector);
	  Vector transform_pos(Vector);
	  Vector transform_normal(Vector);
	  Vector vector_multiply(Matrix, Vector);
	  Matrix inverse(Matrix);
	  //void print();
};

#endif