#ifndef LOCALGEO_H
#define LOCALGEO_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"

using namespace std;

/*Store the local geometry at the intersection point. May need to store other quantities (eg. texture coordinate) in a more complicated raytracer. */

class LocalGeo {
	public:
		Vector pos;
		Vector normal;
		LocalGeo();
		LocalGeo(Vector, Vector);
};

#endif
