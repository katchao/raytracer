#include "color.h"

Color::Color() {
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

Color::Color(float ir, float ig, float ib) {
	r = ir;
	g = ig;
	b = ib;

	r2 = int(r * 255);
	g2 = int(g * 255);
	b2 = int(b * 255);
}

Color::Color(int ir, int ig, int ib) {
}

void Color::add(Color toAdd) {
	r += toAdd.r;
	g += toAdd.g;
	b += toAdd.b;
	r2 += toAdd.r2;
	g2 += toAdd.g2;
	b2 += toAdd.b2;
}