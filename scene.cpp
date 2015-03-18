#include "scene.h"

Scene::Scene() {
	dim_x = 500;
	dim_y = 500;
	UL = Vector(-1,  1, -3);
	UR = Vector( 1,  1, -3);
	LR = Vector( 1, -1, -3);
	LL = Vector(-1, -1, -3);
	
}

Scene::Scene(int x, int y) {
	dim_x = x;
	dim_y = y;
	//dim_z = z;
	UL = Vector(-1,  1, -3);
	UR = Vector( 1,  1, -3);
	LR = Vector( 1, -1, -3);
	LL = Vector(-1, -1, -3);
}


void Scene::render() {
	Sampler sampler = Sampler(dim_x, dim_y);
	Sample sample = Sample();
	Ray ray = Ray();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Film film = Film(dim_x, dim_y);
	camera = Camera(eye, UL, UR, LL, LR, dim_x, dim_y);

	Raytracer raytracer = Raytracer(camera.eye);
	raytracer.list_lights = list_lights;
	raytracer.list_primitives = list_primitives;
	// cout << "Triangles in List Primitives in Render :" << endl;
	// Triangle* triangle = (Triangle*) list_primitives[0];
	// cout << "Vertex Num 1" << " : (" << triangle->v1.x << ", " << triangle->v1.y << ", " << triangle->v1.z << ")" << endl;
	// cout << "Vertex Num 2" << " : (" << triangle->v2.x << ", " << triangle->v2.y << ", " << triangle->v2.z << ")" << endl;
	// cout << "Vertex Num 3" << " : (" << triangle->v3.x << ", " << triangle->v3.y << ", " << triangle->v3.z << ")" << endl;
	
	// cout << "Triangles in RayTracer List Primitives in Scene Render :" << endl;
	// Triangle* triangle1 = (Triangle*) raytracer.list_primitives[0];
	// cout << "Vertex Num 1" << " : (" << triangle1->v1.x << ", " << triangle1->v1.y << ", " << triangle1->v1.z << ")" << endl;
	// cout << "Vertex Num 2" << " : (" << triangle1->v2.x << ", " << triangle1->v2.y << ", " << triangle1->v2.z << ")" << endl;
	// cout << "Vertex Num 3" << " : (" << triangle1->v3.x << ", " << triangle1->v3.y << ", " << triangle1->v3.z << ")" << endl;
	
	
	
	// // Sphere1
	// Color ka = Color(0.1f, 0.1f, 0.1f); Color kd = Color(1.0f, 0.0f, 1.0f); Color ks = Color(1.0f, 1.0f, 1.0f); Color kr = Color(0.0f, 0.0f, 0.0f); float sp = 50.0f;
	// BRDF brdf = BRDF(ka, kd, ks, kr, sp);
	// Material mat1 = Material(&brdf);
	// Sphere sphere1 = Sphere(Vector(0.0f, 0.0f, -20.0f), 3.0f, &mat1); raytracer.list_primitives.push_back(&sphere1);

	// // Sphere2
	// Color ka2 = Color(0.1f, 0.1f, 0.1f); Color kd2 = Color(1.0f, 1.0f, 0.0f); Color ks2 = Color(1.0f, 1.0f, 1.0f); Color kr2 = Color(0.0f, 0.0f, 0.0f); float sp2 = 50.0f;
	// BRDF brdf2 = BRDF(ka2, kd2, ks2, kr2, sp2);
	// Material mat2 = Material(&brdf2);
	// Sphere sphere2 = Sphere(Vector(-2.0f, 2.0f, -15.0f), 1.0f, &mat2); raytracer.list_primitives.push_back(&sphere2);

	// // Sphere3
	// Color ka3 = Color(0.1f, 0.1f, 0.1f); Color kd3 = Color(0.0f, 1.0f, 1.0f); Color ks3 = Color(1.0f, 1.0f, 1.0f); Color kr3 = Color(0.0f, 0.0f, 0.0f); float sp3 = 50.0f;
	// BRDF brdf3 = BRDF(ka3, kd3, ks3, kr3, sp3);
	// Material mat3 = Material(&brdf3);
	// Sphere sphere3 = Sphere(Vector(-2.0f, -2.0f, -15.0f), 1.0f, &mat3); raytracer.list_primitives.push_back(&sphere3);

	// Triangle
	Color ka4 = Color(0.1f, 0.1f, 0.1f); Color kd4 = Color(0.1f, 0.1f, 0.1f); Color ks4 = Color(1.0f, 1.0f, 1.0f); Color kr4 = Color(1.0f, 1.0f, 1.0f); float sp4 = 50.0f;
	BRDF brdf4 = BRDF(ka4, kd4, ks4, kr4, sp4);
	Material mat4 = Material(&brdf4);
	Triangle triangle1 = Triangle(Vector(5.0f, 5.0f, -17.0f), Vector(1.0f, 4.0f, -20.0f), Vector(6.0f, -1.0f, -20.0f), &mat4); raytracer.list_primitives.push_back(&triangle1);
	

	// // Lights
	// DirLight dl1 = DirLight(Vector(0.57735027f, -0.57735027f, -0.57735027f), Color(1.0f, 1.0f, 1.0f));
	// DirLight dl2 = DirLight(Vector(0.57735027f, 0.57735027f, -0.57735027f), Color(0.0f, 0.0f, 1.0f));
	// raytracer.list_lights.push_back(&dl1);
	// raytracer.list_lights.push_back(&dl2);
	// AmbientLight amb = AmbientLight(Color(1.0f, 1.0f, 1.0f));
	// raytracer.list_lights.push_back(&amb);
	

	/////// DEBUGGING
	cout << "Eye Position: "; raytracer.eye.print(); cout << endl;
	cout << "LL: "; camera.LL.print(); cout << endl;
	cout << "LR: "; camera.LR.print(); cout << endl;
	cout << "UL: "; camera.UL.print(); cout << endl;
	cout << "UR: "; camera.UR.print(); cout << endl;

	for(int i = 0; i < raytracer.list_primitives.size(); i++) {
		raytracer.list_primitives[i]->print();
	}
	for(int i = 0; i < raytracer.list_lights.size(); i++) {
		raytracer.list_lights[i]->print();
	}
	/////////// END DEBUGGING

	int counter = 0;
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, counter, &color);
		film.storeSamples(color, sample);
	}
	cout << "Computing Complete.\n";
	film.writeImage();
	cout << "Rendering Complete.\n";
}




int main(int argc, const char* argv[]) {
	/* Vector Debugging */
	Vector test = Vector(1.0f, 2.0f, 3.0f);
	Vector add = test + test;
	cout << "add rseult: "; add.print(); cout << endl;
	Vector sub = test - test;
	cout << "sub rseult: "; sub.print(); cout << endl;
	Vector mult = test * test;
	cout << "mult rseult: "; mult.print(); cout << endl;
	Vector mult_f = test * 2.0f;
	cout << "mult rseult: "; mult_f.print(); cout << endl;
	Vector div = test / add;
	cout << "div rseult: "; div.print(); cout << endl;
	Vector div_f = test / 2.0f;
	cout << "div float rseult: "; div_f.print(); cout << endl;
	float dot_prod = dot_product(add, mult);
	cout << "dot prod rseult: "<< dot_prod << endl;

	Scene scene = Scene();
	bool fileExists = false;
	// parse input file
	if(argc == 2) {
		scene.parse_input(argv[1], fileExists);
	}
	//if there is a file then parse the file
	if (fileExists) {
		ObjParser objparser = ObjParser(scene.file);
		vector<Primitive*> objparser_triangles;
		objparser_triangles = objparser.parse();

		for (int k = 0; k<objparser_triangles.size();k++) {
		Triangle* triangle1 = (Triangle*) objparser_triangles[k];
		Vector vert1 = Vector(); vert1.x = triangle1->v1.x; vert1.y = triangle1->v1.y; vert1.z = triangle1->v1.z;
		Vector vert2 = Vector(); vert2.x = triangle1->v2.x; vert2.y = triangle1->v2.y; vert2.z = triangle1->v2.z;
		Vector vert3 = Vector(); vert3.x = triangle1->v3.x; vert3.y = triangle1->v3.y; vert3.z = triangle1->v3.z;
		Triangle triangle = Triangle(vert1, vert2, vert3, scene.list_materials[scene.list_materials.size() - 1]);
		
		scene.list_primitives.push_back(&triangle);

		}
	}
	if (!scene.list_primitives.empty()) { scene.render();}
	
	else {cout << "There is nothing to render." << endl;}


	return 0;
}



void Scene::parse_input(const char* input_file, bool& isFile) {
	const int MAX_CHARS_PER_LINE = 512;
	const int MAX_TOKENS_PER_LINE = 20;
	const char* const DELIMITER = " ";

	ifstream fin;
	fin.open(input_file); // open a file

	if (!fin.good()) { 
		return; // exit if file not found
	}

	 // read each line of the file
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);
    
		// parse the line into blank-delimited tokens
		int n = 0;
    
		// array to store memory addresses of the tokens in buf
		const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
		// parse the line
		token[0] = strtok(buf, DELIMITER); // first token
		if (token[0]) { // zero if line is blank
		  for (n = 1; n < MAX_TOKENS_PER_LINE; n++) {
			token[n] = strtok(0, DELIMITER); // subsequent tokens
			if (!token[n]) break; // no more tokens
		  }
		}

		// process tokens
		for (int i = 0; i < n; i++) { // n = #of tokens
			if(strcmp(token[i], "cam") == 0) { //cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz
				eye = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				LL = Vector((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				LR = Vector((float) atof(token[i+7]), (float) atof(token[i+8]), (float) atof(token[i+9]));
				UL = Vector((float) atof(token[i+10]), (float) atof(token[i+11]), (float) atof(token[i+12]));
				UR = Vector((float) atof(token[i+13]), (float) atof(token[i+14]), (float) atof(token[i+15]));
			}

			else if(strcmp(token[i], "mat") == 0) { //mat kar kag kab kdr kdg kdb ksr ksg ksb ksp krr krg krb 
				Color ka = Color((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Color kd = Color((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				Color ks = Color((float) atof(token[i+7]), (float) atof(token[i+8]), (float) atof(token[i+9]));
				float sp = (float) atof(token[i+10]);
				Color kr = Color((float) atof(token[i+11]), (float) atof(token[i+12]), (float) atof(token[i+13]));
				BRDF* brdf = new BRDF(ka, kd, ks, kr, sp);
				Material* material = new Material(brdf);

				list_materials.push_back(material);
			}

			else if(strcmp(token[i], "ltp") == 0) { //ltp px py pz r g b [falloff]
				Vector pos = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Color intensity = Color((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				PointLight* pl = new PointLight(pos, intensity);
				pl->falloff = (float) atof(token[i+7]);

				list_lights.push_back((Light*) pl);
			}

			else if(strcmp(token[i], "ltd") == 0) { //ltp px py pz r g b [falloff]
				Vector pos = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Color intensity = Color((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				DirLight* dl = new DirLight(pos, intensity);

				list_lights.push_back((Light*) dl);
			}

			else if(strcmp(token[i], "lta") == 0) { //lta r g b 
				Color intensity = Color((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				AmbientLight* al = new AmbientLight(intensity);

				list_lights.push_back((Light*) al);
			}

			else if(strcmp(token[i], "sph") == 0) { //sph cx cy cz r
				Vector center = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				float radius = (float) atof(token[i+4]);
				if(list_materials.size() > 0) {
					Sphere* sphere = new Sphere(center, radius, list_materials[list_materials.size()-1]);
					list_primitives.push_back(sphere);
				}
			}

			else if(strcmp(token[i], "tri") == 0) { //tri ax ay az bx by bz cx cy cz 
				Vector v1 = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Vector v2 = Vector((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				Vector v3 = Vector((float) atof(token[i+7]), (float) atof(token[i+8]), (float) atof(token[i+9]));
				if(list_materials.size() > 0) {
					Triangle* triangle = new Triangle(v1, v2, v3, list_materials[list_materials.size()-1]);
					list_primitives.push_back(triangle);
				}
			}

			else if (strcmp(token[i], "obj") == 0) { // obj file_name
				file = token[i+1];
				isFile = true;
			}

			// else if (token[i]) { // the warning messages for if this string is not something supported
			// 	cerr << "I don't understand. This feature is unsupported." << token[i] << endl;
			// 	break;
			// }
		}
	}
}