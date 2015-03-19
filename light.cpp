#include "light.h"

void Light::print() {
	cout << "Light pos: "; pos.print(); cout << " color: "; color.print(); cout << "type: " << type << endl;
}

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

PointLight::PointLight(Vector ipos, Color irgb, float ifalloff) : Light() {
	pos = ipos;
	color = irgb;
	type = 1;
	falloff = ifalloff;
}

AmbientLight::AmbientLight() : Light() {
	pos = Vector();
	color =  Color();
	type = 2;
}

AmbientLight::AmbientLight(Color irgb) : Light() {
	pos = Vector();
	color = irgb;
	type = 2;
}



/* This is an abstract class that will generate a ray starting from
*  the position stored in local to the position of the light source.
*  For directional light, the origin of the ray is the same, and the 
*  ray points to the light direction, however, t_max is infinity.*/
void Light::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
	//create light ray from current position (on object) to light source
	// local.pos = current position
	lray->start = local.pos;

	// direction of light ray = source of light - currPos
	Vector direction = pos - local.pos;
	//cout << "Current position: "; local.pos.print(); cout << endl;
	//cout << "Light position: "; pos.print(); cout << endl;
	//cout << "Lray Direction: "; direction.print(); cout << endl << endl;
	lray->dir = direction;
	if(type == 0) { // if directional light, multiply by -1
		lray->dir = direction * -1.0f;
	}
	if(type == 0) {
		lray->t_max = INFINITY;
	}
	//cout << "Lray1: "; lray->print(); cout << endl;
	*lcolor = color;
}



