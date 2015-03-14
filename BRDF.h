#ifndef BRDF_H
#define BRDF_H

#include <iostream>
#include "color.h"

using namespace std;

// Iterates through every pixel in the screen

class BRDF {
  public:
	Color kd, ks, ka, kr;

	BRDF(Color, Color, Color, Color);
};

#endif