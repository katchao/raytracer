#include "scene.h"

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
	Camera camera = Camera(eye_position, UL, UR, LL, LR, dim_x, dim_y);

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

int main() {
	//vector<Primitive*> primitives;
	Scene scene = Scene(Vector(0.0f, 0.0f, 0.0f), 500, 500);
	ObjParser parser = ObjParser("simplesquare.obj");
	//scene.primitives = parser.parse();
	cout << " I am about to render homie." << endl;
	scene.render();


	//want to print out the size of the buckets
	return 0;
}