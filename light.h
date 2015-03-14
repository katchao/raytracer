#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "sphere.h"

using namespace std;

class Light {
	public:
		Vector pos;
		Color color;
		/*Light takes in position, color, and if it is directional or not*/
		Light(Vector, Color);

		/* This is an abstract class that will generate a ray starting from
        *  the position stored in local to the position of the light source.
        *  For directional light, the origin of the ray is the same, and the 
        *  ray points to the light direction, however, t_max is infinity.*/
		Ray* generateLightRay(Vector&, Ray*, Color*);

		
};

#endif
