#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <cmath>
#include "BRDF.h"
#include "localgeo.h"
#include "color.h"
#include <vector>

using namespace std;

class Material {
  public:
	BRDF* constantBRDF;

	Material();
	Material(BRDF*);
	//void getBRDF(LocalGeo&, BRDF*);
	void print();
};

#endif