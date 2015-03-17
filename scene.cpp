#include "scene.h"

Scene::Scene() {
}

Scene::Scene(Vector eye, int x, int y) {
	vector<Primitive*> primitives;
	eye_position = eye;
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
	camera = Camera(eye_position, UL, UR, LL, LR, dim_x, dim_y);

	Raytracer raytracer = Raytracer(eye_position);
	cout << "I made a raytracer homie" << endl;
	//raytracer.list_primitives = primitives;
	cout << "I set primitives homie. But is it correct?" << endl;

	/*
	for (int k = 0; k<scene.primitives.size(); k++) {
		Triangle* triangle = scene.primitives[k];
		cout << "Triangle Number" << k + 1 << endl;
		cout << "Vertex Num 1" << " : (" << triangle->v1.x << ", " << triangle->v1.x << ", " << raytracer.list_primitives[k]->v1.x << ")" << endl;
		cout << "Vertex Num 2" << " : (" << triangle->v2.x << ", " << raytracer.list_primitives[k]->v2.y << ", " << raytracer.list_primitives[k]->v2.z << ")" << endl;
		cout << "Vertex Num 3" << " : (" << raytracer.list_primitives[k]->v3.x << ", " << raytracer.list_primitives[k]->v3.y << ", " << raytracer.list_primitives[k]->v3.z << ")" << endl;
	}*/

	
	// Sphere1
	Color ka = Color(0.1f, 0.1f, 0.1f); Color kd = Color(1.0f, 0.0f, 1.0f); Color ks = Color(1.0f, 1.0f, 1.0f); Color kr = Color(0.0f, 0.0f, 0.0f); float sp = 50.0f;
	BRDF brdf = BRDF(ka, kd, ks, kr, sp);
	Material mat1 = Material(brdf);
	Sphere sphere1 = Sphere(Vector(0.0f, 0.0f, -20.0f), 3.0f, &mat1); raytracer.list_primitives.push_back(&sphere1);

	// Sphere2
	Color ka2 = Color(0.1f, 0.1f, 0.1f); Color kd2 = Color(1.0f, 1.0f, 0.0f); Color ks2 = Color(1.0f, 1.0f, 1.0f); Color kr2 = Color(0.0f, 0.0f, 0.0f); float sp2 = 50.0f;
	BRDF brdf2 = BRDF(ka2, kd2, ks2, kr2, sp2);
	Material mat2 = Material(brdf2);
	Sphere sphere2 = Sphere(Vector(-2.0f, 2.0f, -15.0f), 1.0f, &mat2); raytracer.list_primitives.push_back(&sphere2);

	// Sphere3
	Color ka3 = Color(0.1f, 0.1f, 0.1f); Color kd3 = Color(0.0f, 1.0f, 1.0f); Color ks3 = Color(1.0f, 1.0f, 1.0f); Color kr3 = Color(0.0f, 0.0f, 0.0f); float sp3 = 50.0f;
	BRDF brdf3 = BRDF(ka3, kd3, ks3, kr3, sp3);
	Material mat3 = Material(brdf3);
	Sphere sphere3 = Sphere(Vector(-2.0f, -2.0f, -15.0f), 1.0f, &mat3); raytracer.list_primitives.push_back(&sphere3);

	// Triangle
	Color ka4 = Color(0.1f, 0.1f, 0.1f); Color kd4 = Color(0.1f, 0.1f, 0.1f); Color ks4 = Color(1.0f, 1.0f, 1.0f); Color kr4 = Color(0.0f, 0.0f, 0.0f); float sp4 = 50.0f;
	BRDF brdf4 = BRDF(ka4, kd4, ks4, kr4, sp4);
	Material mat4 = Material(brdf4);
	Triangle triangle1 = Triangle(Vector(5.0f, 5.0f, -17.0f), Vector(1.0f, 4.0f, -20.0f), Vector(6.0f, -1.0f, -20.0f), &mat4); raytracer.list_primitives.push_back(&triangle1);

	// Lights
	DirLight dl1 = DirLight(Vector(0.57735027f, -0.57735027f, -0.57735027f), Color(1.0f, 1.0f, 1.0f));
	DirLight dl2 = DirLight(Vector(0.57735027f, 0.57735027f, -0.57735027f), Color(0.0f, 0.0f, 1.0f));
	raytracer.list_lights.push_back(dl1);
	raytracer.list_lights.push_back(dl2);

	int counter = 0;
	while (sampler.getSample(&sample)) {
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, counter, &color);
		film.storeSamples(color, sample);
		counter++;
	}
	cout << "Computing Complete.\n";
	film.writeImage();
	cout << "Rendering Complete.\n";
}




int main(int argc, const char* argv[]) {
	//ObjParser parser = ObjParser("simplesquare.obj");
	Scene scene = Scene(Vector(0.0f, 0.0f, 0.0f), 500, 500);

	// parse input file
	if(argc == 2) {
		scene.parse_input(argv[1]);
	}
	scene.render();

	return 0;
}



void Scene::parse_input(const char* input_file) {
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
			cout << "Token[" << i << "] = " << token[i] << endl;
		
			if(strcmp(token[i], "cam") == 0) { //cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz
				camera.eye = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				camera.LL = Vector((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				camera.LR = Vector((float) atof(token[i+7]), (float) atof(token[i+8]), (float) atof(token[i+9]));
				camera.UL = Vector((float) atof(token[i+10]), (float) atof(token[i+11]), (float) atof(token[i+12]));
				camera.UR = Vector((float) atof(token[i+13]), (float) atof(token[i+14]), (float) atof(token[i+15]));
			}

			else if(strcmp(token[i], "mat") == 0) { //mat kar kag kab kdr kdg kdb ksr ksg ksb ksp krr krg krb 
				Color ka = Color((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Color kd = Color((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				Color ks = Color((float) atof(token[i+7]), (float) atof(token[i+8]), (float) atof(token[i+9]));
				float sp = (float) atof(token[i+10]);
				Color kr = Color((float) atof(token[i+11]), (float) atof(token[i+12]), (float) atof(token[i+13]));
				BRDF brdf = BRDF(ka, kd, ks, kr, sp);
				Material material = Material(brdf);

				list_materials.push_back(&material);
			}

			else if(strcmp(token[i], "ltp") == 0) { //ltp px py pz r g b [falloff]
				Vector pos = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				Color intensity = Color((float) atof(token[i+4]), (float) atof(token[i+5]), (float) atof(token[i+6]));
				PointLight pl = PointLight(pos, intensity);
				pl.falloff = (float) atof(token[i+7]);

				list_lights.push_back(&pl);
			}

			else if(strcmp(token[i], "sph") == 0) { //sph cx cy cz r
				Vector center = Vector((float) atof(token[i+1]), (float) atof(token[i+2]), (float) atof(token[i+3]));
				float radius = (float) atof(token[i+4]);
				if(list_materials.size() > 0) {
					Material* mat = list_materials[list_materials.size()-1];
					Sphere sphere = Sphere(center, radius, mat);
					list_primitives.push_back(&sphere);
				}
			}
		}
		cout << endl;
	}
}

//#include "scene.h"
//
//Scene::Scene() {
//}
//
//Scene::Scene(Vector eye, int x, int y) {
//	vector<Primitive*> primitives;
//	eye_position = eye;
//	dim_x = x;
//	dim_y = y;
//	//dim_z = z;
//}
//
//
//void Scene::render() {
//	Sampler sampler = Sampler(dim_x, dim_y);
//	Sample sample = Sample();
//	Ray ray = Ray();
//	Color color = Color(0.0f, 0.0f, 0.0f);
//	Film film = Film(dim_x, dim_y);
//	camera.nx = dim_x;
//	camera.ny = dim_y;
//
//	Raytracer raytracer = Raytracer(eye_position);
//	
//	// Corners
//	UL = Vector(-1,  1, -3);
//	UR = Vector( 1,  1, -3);
//	LR = Vector( 1, -1, -3);
//	LL = Vector(-1, -1, -3);
//
//	// Sphere1
//	Color ka = Color(0.1f, 0.1f, 0.1f); Color kd = Color(1.0f, 0.0f, 1.0f); Color ks = Color(1.0f, 1.0f, 1.0f); Color kr = Color(0.0f, 0.0f, 0.0f); float sp = 50.0f;
//	BRDF brdf = BRDF(ka, kd, ks, kr, sp);
//	Material mat1 = Material(brdf);
//	Sphere sphere1 = Sphere(Vector(0.0f, 0.0f, -20.0f), 3.0f, &mat1); raytracer.list_primitives.push_back(&sphere1);
//
//	// Sphere2
//	Color ka2 = Color(0.1f, 0.1f, 0.1f); Color kd2 = Color(1.0f, 1.0f, 0.0f); Color ks2 = Color(1.0f, 1.0f, 1.0f); Color kr2 = Color(0.0f, 0.0f, 0.0f); float sp2 = 50.0f;
//	BRDF brdf2 = BRDF(ka2, kd2, ks2, kr2, sp2);
//	Material mat2 = Material(brdf2);
//	Sphere sphere2 = Sphere(Vector(-2.0f, 2.0f, -15.0f), 1.0f, &mat2); raytracer.list_primitives.push_back(&sphere2);
//
//	// Sphere3
//	Color ka3 = Color(0.1f, 0.1f, 0.1f); Color kd3 = Color(0.0f, 1.0f, 1.0f); Color ks3 = Color(1.0f, 1.0f, 1.0f); Color kr3 = Color(0.0f, 0.0f, 0.0f); float sp3 = 50.0f;
//	BRDF brdf3 = BRDF(ka3, kd3, ks3, kr3, sp3);
//	Material mat3 = Material(brdf3);
//	Sphere sphere3 = Sphere(Vector(-2.0f, -2.0f, -15.0f), 1.0f, &mat3); raytracer.list_primitives.push_back(&sphere3);
//
//	// Triangle
//	Color ka4 = Color(0.1f, 0.1f, 0.1f); Color kd4 = Color(0.1f, 0.1f, 0.1f); Color ks4 = Color(1.0f, 1.0f, 1.0f); Color kr4 = Color(0.0f, 0.0f, 0.0f); float sp4 = 50.0f;
//	BRDF brdf4 = BRDF(ka4, kd4, ks4, kr4, sp4);
//	Material mat4 = Material(brdf4);
//	Triangle triangle1 = Triangle(Vector(5.0f, 5.0f, -17.0f), Vector(1.0f, 4.0f, -20.0f), Vector(6.0f, -1.0f, -20.0f), &mat4); raytracer.list_primitives.push_back(&triangle1);
//
//	// Lights
//	DirLight dl1 = DirLight(Vector(0.57735027f, -0.57735027f, -0.57735027f), Color(1.0f, 1.0f, 1.0f));
//	DirLight dl2 = DirLight(Vector(0.57735027f, 0.57735027f, -0.57735027f), Color(0.0f, 0.0f, 1.0f));
//	raytracer.list_lights.push_back(dl1);
//	raytracer.list_lights.push_back(dl2);
//	
//	cout << "Eye Position: "; eye_position.print(); cout << endl;
//	cout << "UL: "; UL.print(); cout << endl;
//	cout << "UR: "; UR.print(); cout << endl;
//	cout << "LL: "; LL.print(); cout << endl;
//	cout << "LR: "; LR.print(); cout << endl;
//	cout << "list_primitives size: " << raytracer.list_primitives.size() << endl;
//
//	for(int i = 0; i < list_primitives.size(); i++) {
//		list_primitives[i]->print();
//	}
//
//	int counter = 0;
//	while (sampler.getSample(&sample)) {
//		camera.generateRay(sample, &ray);
//		raytracer.trace(ray, counter, &color);
//		film.storeSamples(color, sample);
//		counter++;
//	}
//	cout << "Computing Complete.\n";
//	film.writeImage();
//	cout << "Rendering Complete.\n";
//}
//

//
//int main(int argc, const char* argv[]) {
//	Scene scene = Scene();
//	scene.dim_x = 300;
//	scene.dim_y = 300;
//
//	// parse input file
//	if(argc == 2) {
//		scene.parse_input(argv[1]);
//	}
//	else {
//		scene.eye_position = Vector(0.0f, 0.0f, 0.0f);
//	}
//	scene.render();
//
//	return 0;
//}