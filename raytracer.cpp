#include "raytracer.h"

Raytracer::Raytracer() {
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	Sphere sphere = list_primitives[0];

	float thit;
	LocalGeo local = LocalGeo(); /* WORK ON THIS */
	bool has_intersected = sphere.intersect(ray, &thit, &local);

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
	BRDF brdf = BRDF(ka, kd, ks, kr);

	Ray lray = Ray();
	Color lcolor = Color(0.0f, 0.0f, 0.0f);
	*color = Color(0.0f, 0.0f, 0.0f); //reset color

	// loop through all the lights
	for(int i = 0; i < list_lights.size(); i++) {
		list_lights[i].generateLightRay(local, &lray, &lcolor);

		// TO DO: Check to see if it's blocked

		color->add(shading(local, brdf, lray, lcolor, list_lights[i]));
	}
	cout << "List_lights.size(): " << list_lights.size() << endl;
	cout << "Color = r:" << color->r << " g:" << color->g << " b:" << color->b << endl;

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


	// add ambient term
	color.add(brdf.ka);

	//   Diffuse term = kd*I*max(l*n, 0)
		// l = direction of light, Light.pos vector
		// 	point light - l = location of light - current location on sphere (ijz)
		// 	diffuse light - l = xyz input from command line
		// multiple lights = calculate l vector for each light, compute diffuse term for each light, and then add it all together for final diffuse value

		if(light.type == 1) { // if point light
			//std::cout << "Positions of Light " << pl_list.size() << q << j << i;

			/*
			lray->pos.x = light->pos.x*radius-x;
			lray->pos.y = light->pos.y*radius-y;
			lray->pos.z = light->pos.z*radius-z;*/

			lray.start.normalize();
			lray.dir.normalize();

			float dotProdln = lray.dir.dot_product(local.normal);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
			diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
			diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		}
		/*
		for (int q = 0; q < dl_list.size(); q++) {
			Light light = dl_list[q];
			light.pos[0] = light.pos[0]*radius*-1;
			light.pos[1] = light.pos[1]*radius*-1;
			light.pos[2] = light.pos[2]*radius*-1;
			light.pos = normalize(light.pos);

			float dotProdln = dot_product(light.pos, n);
			float maxdotProd = max(dotProdln, 0.0f);

			diffuse[0] += kd[0] * light.color[0] * maxdotProd;
			diffuse[1] += kd[1] * light.color[1] * maxdotProd;
			diffuse[2] += kd[2] * light.color[2] * maxdotProd;
		}*/
		color.add(diffuse);
		return color;

}