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
		/*Light takes in position, color, and if it is directional or not*/
		Light(Vector, Color, bool);

		Vector pos;
		Color color;
		bool isdir;
		
};

#endif
