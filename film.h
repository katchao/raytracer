#ifndef FILM_H
#define FILM_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "vector.h"

//#include "sample.h"

using namespace std;

class Film {
	public:
		/*
	  	static int dim_x;
	  	static int dim_y;*/
	  	int dim_y; 
	  	int dim_x;

	  	/*Takes in the dimentions of the image for iterationp purposes.*/
	  	Film(int, int);

		/*Adds the colors to the sample's bucket in the buckets array*/
	  	void storeSamples(Vector, int, int);

		/* write image to file */
		void writeImage();

		/*Stores the samples*/
	  	vector<vector<Vector> >buckets;	
};

#endif