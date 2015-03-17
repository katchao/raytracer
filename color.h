#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

class Color {
  public:
	float r, g, b;
	int r2, g2, b2;


	Color();
	Color(float, float, float);
	Color(int, int, int);

	void add (Color);
	void print();
	float sum();
};

#endif