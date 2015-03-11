#include "sample.h"

Sample::Sample() {
	x = 0.0;
	y = 0.0;
	//z = 0.0;
}

Sample::Sample(float ix, float iy) {
	x = ix;
	y = iy;
	//z = iz;
}

// prints out vectors in the form of (x, y)
std::ostream& operator<<(std::ostream &strm, Sample s) {
  return strm << "(" << s.x << ", " << s.y << ")";
}