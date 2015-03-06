#include <vector>
#include "film.h"
#include "vector.h"

/* You will make one Film class for each rendered image.
** The Film object will take in the dimentions of the image.
** It will then make a 2D array buckets based on the dimentions.
** At each point it will store the color vector.*/

Film::Film(int x, int y) {
	dim_x = x; dim_y = y;
}

vector<vector<Vector> > buckets;

void Film::storeSamples(Vector color, int x, int y){
	//make an array to store the pixel samples
	if (x < buckets.size()) {
		buckets[x].push_back(color);
	 }
	vector<Vector> tempX;
	tempX.push_back(color);
	buckets.push_back(tempX);
	//maybe delete tempY

}
//For now Print the pos of pixel and color of the vector
void Film::writeImage(){

	FILE *output = fopen("output.ppm", "wb");
	fprintf(output, "P3\n");
	fprintf(output, "%d %d\n", dim_x, dim_y);
	fprintf(output, "255\n ");

	for(int i=0; i<=dim_x; i++) {
		cout << "size of Y dimention: " << buckets[i].size() << "\n";
		for (int j=0; j<=dim_y;j++) {
			Vector color = buckets[i][j];
			cout << "My Color (" << color.x << "," << color.y << "," << color.z <<")\n";
			fprintf(output, "%d %d %d ", 255, 0, 255 );
		}
	}

	fclose(output);
}
