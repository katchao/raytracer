#include "material.h"

Material::Material() {
}

Material::Material(BRDF* ibrdf) {
	constantBRDF = ibrdf;
}

/*
void BRDF::getBRDF(LocalGeo& local, BRDF* brdf) {
}
*/

void Material::print() {
	constantBRDF->print();
}