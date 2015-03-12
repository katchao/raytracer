#include "sampler.h"
#include "color.h"

Sampler::Sampler() {
	curx = 0.5f;
	cury = 0.5f;
	boundx = 0;
	boundy = 0;
}

Sampler::Sampler(int x, int y) {
	curx = 0.5f;
	cury = 0.5f;
	boundx = x;
	boundy = y;
}

// get the next pixel in the screen
bool Sampler::getSample(Sample* sample) {
	if(curx > boundx) { //end of line, go to the next line
		cury = cury + 1.0f;
		if(cury > boundy) { // out of bounds
			return false;
		}
		curx = 0.5f; //set x back to beginning if the function didn't return false (new line case)
	}

	*sample = Sample(curx, cury); // new sample
	//cout << "Sample: (" << sample->x << ", " << sample->y << ")";
	//cout << "Cur: (" << curx << ", " << cury << ")" << endl;

	curx = curx + 1.0f;
	return true;

}