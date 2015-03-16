#include "light.h"


/*
Light::Light(Vector ipos, Color rgb) {
	pos = ipos;
	color = rgb;
}*/

DirLight::DirLight(Vector ipos, Color irgb) : Light() {
	pos = ipos;
	color = irgb;
	type = 0;
}

PointLight::PointLight(Vector ipos, Color irgb) : Light() {
	pos = ipos;
	color = irgb;
	type = 1;
}



/* This is an abstract class that will generate a ray starting from
*  the position stored in local to the position of the light source.
*  For directional light, the origin of the ray is the same, and the 
*  ray points to the light direction, however, t_max is infinity.*/
void Light::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
	//create light ray from current position (on object) to light source
	// local.pos = current position
	lray->start = local.pos;

	// direction of light ray = currentPos - source of light
	Vector direction = Vector();
	direction.subtract(pos, local.pos);
	lray->dir = direction;

	if(type == 0) {
		lray->t_max = INFINITY;
	}

	*lcolor = color;
}



