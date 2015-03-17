#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>
#include <cmath>
#include "vector.h"
#include "ray.h"
#include "intersection.h"
#include "material.h"

using namespace std;

class Intersection;
class Material;

class Primitive {
  public:
	  virtual ~Primitive();

	  bool type; // 0 for sphere, 1 for triangle
	  Material* mat;
	  virtual bool intersect(Ray& ray, float* thit, Intersection* in);
	  virtual bool intersectP(Ray& ray);
	  virtual void print();
};

class Sphere : public Primitive {
	public:
	  	Vector center; 
	  	float radius;

		Sphere();
		Sphere(Vector, float);
		Sphere(Vector, float, Material*);
		bool intersect(Ray&, float*, Intersection*);
		bool intersectP(Ray&);
		void print();

};


class Triangle : public Primitive {
	public:
	  	Vector v1, v2, v3;//3 vertices

		Triangle();
		Triangle(Vector, Vector, Vector);
		Triangle(Vector, Vector, Vector, Material*);
		bool intersect(Ray&, float*, Intersection*);
		bool intersectP(Ray&);
		void print();

};

#endif