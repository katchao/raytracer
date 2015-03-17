#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <cmath>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "localgeo.h"

using namespace std;

class Light {
	public:
		Vector pos;
		Color color;
		bool type; /* 0 for directional, 1 for point light */

		/* This is an abstract class that will generate a ray starting from
        *  the position stored in local to the position of the light source.
        *  For directional light, the origin of the ray is the same, and the 
        *  ray points to the light direction, however, t_max is infinity.*/
		void generateLightRay(LocalGeo&, Ray*, Color*);
		void print();
};

class DirLight : public Light {
	// the pos vector is the direction 
	public:
		DirLight(Vector, Color);

};

class PointLight : public Light {
	//for point light the pos is the position of the light
	public:
		float falloff;
		PointLight(Vector, Color);
		PointLight(Vector, Color, float);
};

class AmbientLight : public Light {
	public:
		AmbientLight();
		AmbientLight(Color);
};


#endif
