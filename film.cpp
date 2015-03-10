#include <vector>
#include "film.h"
#include "vector.h"
#include "color.h"

/* You will make one Film class for each rendered image.
** The Film object will take in the dimentions of the image.
** It will then make a 2D array buckets based on the dimentions.
** At each point it will store the color vector.*/

Film::Film(int x, int y) {
	dim_x = x; dim_y = y;
}

vector<vector<Color> > buckets;

void Film::storeSamples(Color &color, Sample& sample){
	//make an array to store the pixel samples
	Color new_color = Color(color.r, color.g, color.b);
	int x = sample.x;
	int y = sample.y;
	if (x < buckets.size()) {
		buckets[x].push_back(new_color);
	 }
	vector<Color> tempX;
	tempX.push_back(new_color);
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
		//cout << "size of Y dimention: " << buckets[i].size() << "\n";
		for (int j=0; j<=dim_y;j++) {
			Color color = buckets[i][j];
			cout << "My Color Bucket (" << color.r2 << "," << color.g2 << "," << color.b2 << ") at " << i << ", " << j << ")\n";
			fprintf(output, "%d %d %d     ", color.r2, color.g2, color.b2);
		}
		fprintf(output, "\n");
	}

	fclose(output);
}
