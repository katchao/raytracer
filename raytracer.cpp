#include "raytracer.h"

Raytracer::Raytracer(Vector ieye) {
	eye = ieye;
	amb = AmbientLight();
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
			*color = brdf.ka;
			//cout << "shadows triggered" << endl;
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

	lray.dir.normalize();
	light.pos.normalize();
	local.normal.normalize();

	Vector neg_lightPos = Vector();
	neg_lightPos.scalar_multiply(light.pos, -1.0f);
	neg_lightPos.normalize();

	// add ambient term if ambient light
	if(amb.color.sum()) {
		color.add(brdf.ka);
	}

	//   Diffuse term = kd*I*max(l*n, 0)
		// l = direction of light, lray.dir vector
		// 	point light - l = location of light - current location on sphere (ijz)
		// 	diffuse light - l = xyz input from command line
		// multiple lights = calculate l vector for each light, compute diffuse term for each light, and then add it all together for final diffuse value

		if(light.type == 1) { // if point light
			float dotProdln = lray.dir.dot_product(local.normal);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
			diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
			diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		}
		
		if(light.type == 0) { // if directional light
			float dotProdln = neg_lightPos.dot_product(local.normal);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
			diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
			diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		}
		
		//cout << "Diffuse light: "; diffuse.print(); cout << endl;

		//Specular term = ks* I * max(r*v, 0)^p
		//r = reflected direction, r = -l + 2(l*n)n
		// n = local.normal
		// v = eye

		// calculate r
		Vector r = Vector();
		float dotprodln = neg_lightPos.dot_product(local.normal);
		Vector term2 = Vector(); term2.scalar_multiply(local.normal, 2.0f * dotprodln);
		r.add(light.pos, term2);
		if(light.type == 0) { // if directional light
			r.scalar_multiply(r, -1.0f);
		}
		r.normalize();

		float dotProdrv = r.dot_product(light.pos); // TO DO: right now we're hardcoding the eye :(
		float dotProdrvmax = pow(max(dotProdrv, 0.0f), brdf.sp);

		specular.r = brdf.ks.r * lcolor.r * dotProdrvmax;
		specular.g = brdf.ks.g * lcolor.g * dotProdrvmax;
		specular.b = brdf.ks.b * lcolor.b * dotProdrvmax;
		color.add(diffuse); color.add(specular);
		return color;

}