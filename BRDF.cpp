#include "brdf.h"

// Every object has its own BRDF class

BRDF::BRDF(Color ikd, Color iks, Color ika, Color ikr) {
	kd = ikd;
	ks = iks;
	ka = ika;
	kr = ikr;
}