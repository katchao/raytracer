#include <vector>
#include "film.h"
#include "vector.h"
/* You will make one Film class for each rendered image.
** The Film object will take in the dimentions of the image.
** It will then make a 2D array buckets based on the dimentions.
** At each point it will store the color vector.*/

Film::Film(int x, int y) {
	/*Film::dim_x = x; Film::dim_y = y;*/
	dim_x = x; dim_y = y;
}

vector<vector<Vector> > buckets;

void Film::storeSamples(Vector color, int x, int y){
	//make an array to store the pixel samples
	if (x < buckets.size()) {
		Vector averaged = Vector();
		averaged.add(buckets[x], color);
		averaged.scalar_divide(averaged, 2.0f);
		buckets[x].push_back(averaged);
	 }
	vector<Vector> tempX;
	tempX.push_back(color);
	buckets.push_back(tempX);
	//maybe delete tempY

}

/*Averages over samples.*/
void Film::sampleAverage(vector<Vector> sampleColors) {
	Vector summedVec = Vector();
	for(int i =0;i<=sampleColors.size();i++) {
		summedVec.add(summedVec, colors[i])
	}

}


//For now Print the pos of pixel and color of the vector
void Film::writeImage(){
	for(int i=0; i<=dim_x; i++) {
		cout << "size of Y dimention: " << buckets[i].size() << "\n";
		for (int j=0; j<=dim_y;j++) {
			Vector color = buckets[i][j];
			cout << "My Color (" << color.x << "," << color.y << "," << color.z <<")\n";

		}
	}

}
