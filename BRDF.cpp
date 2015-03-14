#include "brdf.h"

// Every object has its own BRDF class

BRDF::BRDF(Color ika, Color ikd, Color iks, Color ikr) {
	ka = ika;
	kd = ikd;
	ks = iks;
	kr = ikr;
}