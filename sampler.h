#ifndef SAMPLER_H
#define SAMPLER_H

#include <iostream>
#include "sample.h"

using namespace std;

// Iterates through every pixel in the screen

class Sampler {
  public:
	float curx, cury;
	int boundx, boundy;

	Sampler();
	Sampler(int, int);
	bool getSample(Sample* sample);
};

#endif