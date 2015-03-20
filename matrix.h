#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


class Matrix {
  public:
	  float items [4][4];
	  Matrix(); //initializes diagonal matrix (1's down the diagonal)
	  void print();
	  void transpose();
};

float radians(float);
float degrees(float);

Matrix test();
Matrix create_translation(float, float, float);
Matrix create_scale(float, float, float);
Matrix create_rotation_x(float);
Matrix create_rotation_y(float);
Matrix create_rotation_z(float);
Matrix matrix_multiply(Matrix, Matrix);

#endif