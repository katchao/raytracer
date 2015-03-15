#include "raytracer.h"

Raytracer::Raytracer(Vector ieye) {
	eye = ieye;
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	float thit;
	Intersection in = Intersection();
	//Primitive triangle = list_primitives[0];
	Triangle triangle = list_primitives[0];

	/*
	// create aggregate primitives
	vector<Primitive*> primitives;
	for(int k = 0; k < list_primitives.size(); k++) {
		Primitive* shape = &list_primitives[k];
		primitives.push_back(shape);
		cout << shape->type << endl;
	}
	AggregatePrimitive group = AggregatePrimitive(primitives);*/

	//bool has_intersected = group.intersect(ray, &thit, &in);
	bool has_intersected = triangle.intersect(ray, &thit, &in);
	cout << "has_intersected: " << has_intersected << endl;

	// miss
	if(!has_intersected) {
		*color = Color(0.0f, 0.0f, 0.0f);
		return;
	}

	// hit

	// hardcoded BRDF for now
	Color ka = Color(0.05f, 0.05f, 0.05f);
	Color kd = Color(1.0f, 1.0f, 1.0f);
	Color ks = Color(1.0f, 1.0f, 1.0f);
	Color kr = Color(0.0f, 0.0f, 0.0f);
	float sp = 64.0f;
	BRDF brdf = BRDF(ka, kd, ks, kr, sp);

	Ray lray = Ray();
	Color lcolor = Color(0.0f, 0.0f, 0.0f);
	*color = Color(0.0f, 0.0f, 0.0f); //reset color

	// loop through all the lights
	for(int i = 0; i < list_lights.size(); i++) {
		list_lights[i].generateLightRay(in.local, &lray, &lcolor);

		//if (!group.intersectP(lray)) { // If not blocked by anything
		if(!triangle.intersectP(lray)) {
			cout << "this happened";
			color->add(shading(in.local, brdf, lray, lcolor, list_lights[i]));
		}
		else {
			*color = brdf.ka; //add the ambient light for shadows
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

	// add ambient term
	color.add(brdf.ka);

	//   Diffuse term = kd*I*max(l*n, 0)
		// l = direction of light, lray.dir vector
		// 	point light - l = location of light - current location on sphere (ijz)
		// 	diffuse light - l = xyz input from command line
		// multiple lights = calculate l vector for each light, compute diffuse term for each light, and then add it all together for final diffuse value

		lray.dir.normalize();
		if(light.type == 1) { // if point light
			float dotProdln = lray.dir.dot_product(local.normal);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
			diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
			diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		}
		
		if(light.type == 0) { // if directional light
			Vector lightPosDiffuse = Vector();
			lightPosDiffuse.scalar_multiply(light.pos, -1.0f);
			lightPosDiffuse.normalize();

			float dotProdln = lightPosDiffuse.dot_product(local.normal);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
			diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
			diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		}

		//Specular term = ks* I * max(r*v, 0)^p
		//r = reflected direction, r = -l + 2(l*n)n
		// n = local.normal
		// v = eye

		if(light.type == 1) { // if point light
			Vector neg_lightpos = Vector();
			neg_lightpos.scalar_multiply(lray.dir, -1.0);

			// calculate r
			Vector r = Vector();
			float dotprodln = neg_lightpos.dot_product(local.normal);
			Vector term2 = Vector(); term2.scalar_multiply(local.normal, 2.0f * dotprodln);
			r.add(lray.dir, term2);
			r.normalize();

			float dotProdrv = r.dot_product(Vector(0, 0, -1)); // TO DO: right now we're hardcoding the eye :(
			float dotProdrvmax = pow(max(dotProdrv, 0.0f), brdf.sp);

			specular.r = brdf.ks.r * lcolor.r * dotProdrvmax;
			specular.g = brdf.ks.g * lcolor.g * dotProdrvmax;
			specular.b = brdf.ks.b * lcolor.b * dotProdrvmax;
		}

		if(light.type == 0) { // if directional light
			Vector neg_lightpos = Vector();
			neg_lightpos.scalar_multiply(lray.dir, -1.0);

			// calculate r
			Vector r = Vector();
			float dotprodln = neg_lightpos.dot_product(local.normal);
			Vector term2 = Vector(); term2.scalar_multiply(local.normal, 2.0f * dotprodln);
			r.add(lray.dir, term2);
			r.scalar_multiply(r, -1.0f);
			r.normalize();

			float dotProdrv = r.dot_product(Vector(0, 0, -1)); // TO DO: right now we're hardcoding the eye :(
			float dotProdrvmax = pow(max(dotProdrv, 0.0f), brdf.sp);

			specular.r = brdf.ks.r * lcolor.r * dotProdrvmax;
			specular.g = brdf.ks.g * lcolor.g * dotProdrvmax;
			specular.b = brdf.ks.b * lcolor.b * dotProdrvmax;
		}
		color.add(diffuse); color.add(specular);
		return color;

}