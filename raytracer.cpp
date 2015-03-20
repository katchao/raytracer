#include "raytracer.h"

Raytracer::Raytracer(Vector ieye) {
	eye = ieye;
	number_of_transformations = 0;
	// Transformation* initializer = new Transformation();
	// list_transformations.push_back(initializer);
	// cout << "Printing the size in the raytracer constructor\n";
	// cout << " Size = " << list_transformations.size() << endl;
}

void Raytracer::trace(Ray& ray, int depth, Color *color) {
	float thit;
	Intersection in = Intersection();
	const int MAX_DEPTH = 3;
	//cout << "SegFault Raytracer\n";
	AggregatePrimitive group = AggregatePrimitive(list_primitives);//, list_transformations);

	bool has_intersected = false;
	cout << "Size of Transformations = " << number_of_transformations;
	if (number_of_transformations > 0) {
	 	cout << "There is a transformation\n";
	 	has_intersected = group.intersectE(ray, &thit, &in, transform);

	} else {
		has_intersected = group.intersect(ray, &thit, &in);
		
	}
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

	// add ambient light
	color->add(Color(amb->color.r * brdf.ka.r, amb->color.g * brdf.ka.g, amb->color.b * brdf.ka.b));

	for(int i = 0; i < list_lights.size(); i++) {
		Light* currLight = list_lights[i];

		//if not ambient light
		if(currLight->type != 2) {
			currLight->generateLightRay(in.local, &lray, &lcolor);
			//if (!in.primitive->intersectP(lray)) {
			if (!group.intersectP(lray, in.primitive)) {
				//cout << "lray1: "; lray.print(); cout << endl;
				color->add(shading(in.local, brdf, lray, lcolor, *list_lights[i]));
			}
			 else {
		 		//add the ambient light for shadows
				//cout << "current light: "; list_lights[i]->print();
				//cout << "current position: "; in.local.pos.print(); cout << endl;
				//cout << "lray3: "; ray2.print(); cout << endl;
		 		*color = Color(amb->color.r * brdf.ka.r, amb->color.g * brdf.ka.g, amb->color.b * brdf.ka.b);
				 //*color = brdf.ka;
				//cout << "=========================" << endl;
			 }
		}
	}

	//Reflections: if the current Primitive is reflective
	//CHECK!!!!! May not be group->kr!!
	//start is the current position
	//direction is the r reflected vector

	if ((brdf.kr.r + brdf.kr.g + brdf.kr.b != 0.0) && (depth < MAX_DEPTH)) {
		// cout << "BRDF of curr shape = (" << brdf.kr.r << ", " << brdf.kr.g << ", " <<  brdf.kr.b << ")" << endl;
	//At max Depth = 1
	// Max Depth not yet been reached
		// cout << "My Max depth has not been reached" << endl;
		//cout << "Point on shape (" << in.local.pos.x << ", " << in.local.pos.y << ", " << in.local.pos.z << ")\n";
		Color* reflColor = new Color();
		//r = d - 2*(d dot n)*n
		//n - normal to current point
		Vector n_normal = Vector(); n_normal.scalar_multiply(in.local.normal, 1.0f); n_normal.normalize();
		Vector d = Vector(); d.scalar_multiply(lray.dir, 1.0f); d.normalize();
		float d_dot_n = n_normal.dot_product(d); 
		Vector term2 = Vector(); term2.scalar_multiply(n_normal, 2.0f * d_dot_n);
		Vector r = Vector(); r.subtract(d, term2);
		
		//const double ERR = 1e-12; // - Need to offset the reflection rays
		Vector currPos = Vector(); currPos.add(n_normal, lray.start);
		Ray newRay = Ray(currPos, r);
		//cout << "Ray origin (" << newRay.start.x << ", " << newRay.start.y << ", " << newRay.start.z << ")\n";
		//cout << "Ray Direction (" << newRay.dir.x << ", " << newRay.dir.y << ", " << newRay.dir.z << ") \n";

		
		//recursive step
		trace(newRay, depth + 1, reflColor);
		
		reflColor->r = reflColor->r * brdf.kr.r;
		reflColor->g = reflColor->g * brdf.kr.g;
		reflColor->b = reflColor->b * brdf.kr.b;
		// cout << "Color BEFORE the add. = (" << color->r << ", " << color->b << ", " << color->g << ") " << endl;
		color->add(*reflColor);
		// cout << "Color AFTER the add. = (" << color->r << ", " << color->b << ", " << color->g << ") " << endl;

	}
	//Add an isReflective group to the primitives


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

	Vector light_pos = Vector(light.pos.x, light.pos.y, light.pos.z);
	light_pos.normalize();

	//   Diffuse term = kd*I*max(l*n, 0)
		// l = direction of light, lray.dir vector
		// 	point light - l = location of light - current location on sphere (ijz)
		// 	diffuse light - l = xyz input from command line

	 // same computation for directional and point light?

	//if(light.type != 2) { // same computation for directional and point light?
	Vector l = Vector();
	if(light.type == 0) { // directional
		l = light_pos;
	}
	if(light.type == 1) { // point
		l = lray.dir;
	}
	
	//float dotProdln = dot_product(local.normal, l); FIX 1: Point light behaves incorrectly
	float dotProdln = dot_product(local.normal, light_pos);
	float maxdotProd = max(dotProdln, 0.0f);
	diffuse.r = brdf.kd.r * lcolor.r * maxdotProd;
	diffuse.g = brdf.kd.g * lcolor.g * maxdotProd;
	diffuse.b = brdf.kd.b * lcolor.b * maxdotProd;
		//cout << "diffuse: "; diffuse.print(); cout << endl;
	//}

	//   Specular term = ks* I * max(r*v, 0)^p
		// n = local.normal
		// v = eye
	Vector neg_lightPos = light_pos * -1.0f;
	Vector viewer = local.pos - eye;
	viewer.normalize();

	// calculate r = reflected direction, r = -l + 2(l*n)n
	Vector r = (neg_lightPos * -1.0f) + local.normal*(2*dot_product(neg_lightPos, local.normal));

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
