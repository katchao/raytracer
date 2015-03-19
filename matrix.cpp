#include "matrix.h"

Matrix::Matrix() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			items[i][j] = 0.0f;
		}
	}
}