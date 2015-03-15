#include "brdf.h"

// Every object has its own BRDF class

BRDF::BRDF() {
}

BRDF::BRDF(Color ika, Color ikd, Color iks, Color ikr, float isp) {
	ka = ika;
	kd = ikd;
	ks = iks;
	kr = ikr;
	sp = isp;
}