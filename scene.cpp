#include "scene.h"

Scene::Scene(Vector eye, int x, int y) {
	//vector<Primitive*> primitives;
	eye_position = eye;
	dim_x = x;
	dim_y = y;
	//dim_z = z;
	UL = Vector(-1,  1, -1);
	UR = Vector( 1,  1, -1);
	LR = Vector( 1, -1, -1);
	LL = Vector(-1, -1, -1);
}

/*
void render() {
            while (!sampler.generateSample(&sample) {
                        camera.generateRay(sample, &ray);
                        raytracer.trace(ray, &color);
                        film.commit(sample, color);
            }
            film.writeImage();
}
*/

void Scene::render() {
	Sampler sampler = Sampler(dim_x, dim_y);
	Sample sample = Sample();
	Ray ray = Ray();
	Color color = Color(0.0f, 0.0f, 0.0f);
	Film film = Film(dim_x, dim_y);
	Camera camera = Camera(eye_position, UL, UR, LL, LR, dim_x, dim_y);

	Raytracer raytracer = Raytracer(eye_position);
	cout << "I made a raytracer homie" << endl;
	raytracer.list_primitives = primitives;
	cout << "I set primitives homie. But is it correct?" << endl;

	for (int k = 0; k<raytracer.list_primitives.size(); k++) {
		Primitive* triangle = raytracer.list_primitives[k];
		cout << "Triangle Number" << k + 1 << endl;
		cout << "Vertex Num 1" << " : (" << triangle->v1.x << ", " << raytracer.list_primitives[k]->v1.x << ", " << raytracer.list_primitives[k]->v1.x << ")" << endl;
		cout << "Vertex Num 2" << " : (" << triangle->v2.x << ", " << raytracer.list_primitives[k]->v2.y << ", " << raytracer.list_primitives[k]->v2.z << ")" << endl;
		cout << "Vertex Num 3" << " : (" << raytracer.list_primitives[k]->v3.x << ", " << raytracer.list_primitives[k]->v3.y << ", " << raytracer.list_primitives[k]->v3.z << ")" << endl;

	}

	//materials
	// hardcoded BRDF for now
	Color ka = Color(0.05f, 0.05f, 0.05f); Color kd = Color(1.0f, 1.0f, 1.0f); Color ks = Color(1.0f, 1.0f, 1.0f); Color kr = Color(0.0f, 0.0f, 0.0f); float sp = 64.0f;
	BRDF brdf = BRDF(ka, kd, ks, kr, sp);
	Material mat1 = Material(brdf);

	//-ka 0.05 0.05 0.05 -kd 1 1 1 -ks 1 1 1 -sp 64
	Color ka2 = Color(0.05f, 0.05f, 0.05f); Color kd2 = Color(0.6f, 0.5f, 1.0f); Color ks2 = Color(0.2f, 0.0f, 1.0f); Color kr2 = Color(0.0f, 0.0f, 0.0f); float sp2 = 84.0f;
	BRDF brdf2 = BRDF(ka, kd, ks, kr, sp);
	Material mat2 = Material(brdf2);

	//objects
	// Sphere sphere = Sphere(Vector(0.0f, 0.0f, -5.0f), 1.0f); raytracer.list_primitives.push_back(&sphere);
	// Sphere sphere2 = Sphere(Vector(1.0f, 1.0f, -1.2f), 0.3f); raytracer.list_primitives.push_back(&sphere2);
	// Sphere sphere3 = Sphere(Vector(-0.5f, 0.3f, -1.1f), 0.5f); raytracer.list_primitives.push_back(&sphere3);
	// Triangle triangle1 = Triangle(Vector(1.0f, -1.0f, -5.0f), Vector(-1.0f, -1.0f, -5.0f), Vector(1.0f, 1.0f, -5.0f)); raytracer.list_primitives.push_back(&triangle1);

	//lights
	PointLight pl1 = PointLight(Vector(2, 2, 2), Color(1.0f, 0.0f, 0.0f));
	PointLight pl2 = PointLight(Vector(-2, 2, 2), Color(0.0f, 1.0f, 0.0f));
	DirLight pl3 = DirLight(Vector(0, -2, 2), Color(0.0f, 0.0f, 1.0f));
	raytracer.list_lights.push_back(pl1);
	raytracer.list_lights.push_back(pl2);
	raytracer.list_lights.push_back(pl3);

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
	Scene scene = Scene(Vector(0.0f, 0.0f, 0.0f), 200, 200);
	ObjParser parser = ObjParser("simplesquare.obj");
	scene.primitives = parser.parse();
	cout << " I am about to render homie." << endl;
	scene.render();


	//want to print out the size of the buckets
	return 0;
}