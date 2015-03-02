#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <cmath>
#include "vector.h"
//#include "sample.h"

using namespace std;

class Film {
	public:
	  	int dim_x;
	  	int dim_y;
	  	//Samples will have an x and y coordinate and should have a color
	  	//This will store the samples in 2D array.
	  	Film(int, int);

// holds all different samples per pixel
	  	void takeSamples(Vector, int, int);
	  	
	  	/*This will write that color vVctor (bucket) to the pixel in the image file
	  	The ints are the positons of the pixels the color will be set at.*/
	  	void writeSamples(Vector, int, int);

		/* write image to file */
		void writeImage();

	  	//Possible 2D "Bucket" array
	  	//array[x][y] = color_vector
	  	<int>buckets;
};

#endif