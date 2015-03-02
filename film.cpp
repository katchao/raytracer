#include "film.h"
/* You will make one Film class for each rendered image.
** The Film object will take in the dimentions of the image.
** It will then make a 2D array buckets based on the dimentions.
** At each point it will store the color vector.*/

Film::Film(int x, int y) {
	dim_x = x;
	dim_y = y;
}

int buckets[dim_x][dim_y];

void takeSamples(int sample, int x, int y){
	//make an array to store the pixels
	buckets[x][y].push_back(sample);
}
//display sample color
void writeSamples(Vector color, int x, int y){

}
