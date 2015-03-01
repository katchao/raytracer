#ifndef SAMPLER_H
#define SAMPLER_H

#include <iostream>
#include "sample.h"

using namespace std;

class Sampler {
  public:
	bool getSample(Sample* sample);
};

#endif