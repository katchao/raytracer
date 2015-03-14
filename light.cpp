#include "light.h"
#include "vector.h"
#include "film.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "sphere.h"
#include "raytracer.h"
#include <vector>

Light::Light(Vector ipos, Color rgb) {
	pos = ipos;
	color = rgb;
}


/* This is an abstract class that will generate a ray starting from
*  the position stored in local to the position of the light source.
*  For directional light, the origin of the ray is the same, and the 
*  ray points to the light direction, however, t_max is infinity.*/
Ray* Light::generateLightRay(Vector& pos, Ray* lray, Color* Lcolor) {
	
	return lray;

}

