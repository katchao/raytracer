#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

class Film {
	public:
	  	
	  	//This will take in the color vector of the pixel
	  	void takeSamples(Vector, int, int);
	  	
	  	/*This will write that color vVctor (bucket) to the pixel in the image file
	  	The ints are the positons of the pixels the color will be set at.*/
	  	void writeColor(Vector, int, int);

		/* write image to file */
		void writeImage();

	  	//Possible 2D "Bucket" array
	  	//array[x][y] = color_vector
	  	int buckets;
};

#endif