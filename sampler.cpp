#include "sampler.h"

Sampler::Sampler() {
	curx = 0;
	cury = 0;
	boundx = 0;
	boundy = 0;
}

Sampler::Sampler(int x, int y) {
	curx = 0;
	cury = 0;
	boundx = x;
	boundy = y;
}

// get the next pixel in the screen
bool Sampler::getSample(Sample* sample) {

	if(curx > boundx) { //end of line, go to the next line
		cury++;
		if(cury > boundy) { // out of bounds
			return false;
		}
		curx = 0; //set x back to beginning if the function didn't return false (new line case)
	}

	*sample = Sample(curx, cury); // new sample
	//cout << "Sample: (" << sample->x << ", " << sample->y << ")";
	//cout << "Cur: (" << curx << ", " << cury << ")" << endl;

	curx++;
	return true;

}