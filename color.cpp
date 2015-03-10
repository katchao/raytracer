#include "color.h"

Color::Color() {
	r = 0.0;
	g = 0.0;
	b = 0.0;
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