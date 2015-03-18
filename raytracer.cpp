#include "raytracer.h"

Raytracer::Raytracer(Vector ieye) {
	eye = ieye;
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	float thit;
	Intersection in = Intersection();
	AggregatePrimitive group = AggregatePrimitive(list_primitives);
	bool has_intersected = group.intersect(ray, &thit, &in);

	// miss
	if(!has_intersected) {
		*color = Color(0.0f, 0.0f, 0.0f);
		return;
	}

	BRDF brdf = *in.primitive->mat->constantBRDF;

	// hit
	Ray lray = Ray();
	Color lcolor = Color();
	*color = Color(0.0f, 0.0f, 0.0f); //reset color

	// loop through all the lights
	for(int i = 0; i < list_lights.size(); i++) {
		list_lights[i]->generateLightRay(in.local, &lray, &lcolor);
		
		//if (!in.primitive->intersectP(lray)) { // If not blocked by anything
		if (!group.intersectP(lray)) { // If not blocked by anything
			color->add(shading(in.local, brdf, lray, lcolor, *list_lights[i]));
		}
		else {
			//add the ambient light for shadows
			//cout << "shadows";
			//*color = Color(0.0f, 0.0f, 0.0f);
			*color = brdf.ka;
		}
	}

}


// shoot a ray from your eye to the object
// from the intersection, shoot another ray from the intersection to light
// if it hits another object, don't shade it (because that point's being blocked)
// if it hits the light, use phong shading model


// do the phong shading here
Color Raytracer::shading(LocalGeo& local, BRDF& brdf, Ray& lray, Color& lcolor, Light& light) {
	// lray.start = current position on sphere
	// lray.dir = vector to the light position
	Color color = Color();
	Color diffuse = Color();
	Color specular = Color();

	light.pos.normalize();
	local.normal.normalize();

	// add ambient term if ambient light
	if(light.type == 2) {
		Color ambient = Color(lcolor.r * brdf.ka.r, lcolor.g * brdf.ka.g, lcolor.b * brdf.ka.b);
		color.add(ambient);
	}

	//   Diffuse term = kd*I*max(l*n, 0)
		// l = direction of light, lray.dir vector
		// 	point light - l = location of light - current location on sphere (ijz)
		// 	diffuse light - l = xyz input from command line

	//if(light.type != 2) { // same computation for directional and point light?
		float dotProdln = dot_product(local.normal, light.pos);
		float maxdotProd = max(dotProdln, 0.0f);

		diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
		diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
		diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
	//}

	//   Specular term = ks* I * max(r*v, 0)^p
		// n = local.normal
		// v = eye
	Vector neg_lightPos = light.pos * -1.0f;
	Vector viewer = local.pos - eye;
	viewer.normalize();

	// calculate r = reflected direction, r = -l + 2(l*n)n
	// l = lray.dir or light.pos?
	Vector r = (neg_lightPos * -1.0f) + local.normal*(2*dot_product(neg_lightPos, local.normal));
	/*
		Vector r = Vector();
		float dotprodln = dot_product(lray.dir, local.normal);
		Vector term2 = Vector(); term2.scalar_multiply(local.normal, 2.0f * dotprodln);
		r.add(lray.dir * -1.0f, term2);*/
		if(light.type == 0) { // if directional light
			r.scalar_multiply(r, -1.0f);
		}
		r.normalize();
		
		float dotProdrv = r.dot_product(viewer); // TO DO: right now we're hardcoding the eye :(
		float dotProdrvmax = pow(max(dotProdrv, 0.0f), brdf.sp);

	specular.r = brdf.ks.r * lcolor.r * dotProdrvmax;
	specular.g = brdf.ks.g * lcolor.g * dotProdrvmax;
	specular.b = brdf.ks.b * lcolor.b * dotProdrvmax;
	color.add(diffuse); color.add(specular);
	return color;

}