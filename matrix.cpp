#include "matrix.h"

Matrix::Matrix() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(i == j) {
				items[i][j] = 1.0f;
			}
			else {
				items[i][j] = 0.0f;
			}
		}
	}
}

void Matrix::transpose() {
	float tmp;
	
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			tmp = items[i][j];
			items[i][j] = items[j][i];
			items[j][i] = tmp;
		}
	}
}

void Matrix::print() {
	for(int i = 0; i < 4; i++) {
		cout << "[ ";
		for(int j = 0; j < 4; j++) {
			cout << items[i][j] << " ";
		}
		cout << "]" << endl;
	}
}

float radians(float d) {
	return d * M_PI / 180;
}

Matrix create_translation(float tx, float ty, float tz) {
	Matrix result = Matrix();
	result.items[0][3] = tx;
	result.items[1][3] = ty;
	result.items[2][3] = tz;
	return result;
}

Matrix create_scale(float sx, float sy, float sz) {
	Matrix result = Matrix();
	result.items[0][0] = sx;
	result.items[1][1] = sy;
	result.items[2][2] = sz;
	return result;
}

Matrix create_rotation_x(float angle) {
	Matrix result = Matrix();
	angle = radians(angle);
	float c = cos(angle);
	float s = sin(angle);
	// set trig to be 0
	if(abs(c) < 0.0005f) { c = 0.0f; }
	if(abs(s) < 0.0005f) { c = 0.0f; }

	result.items[1][1] = c;
	result.items[1][2] = -s;
	result.items[2][1] = s;
	result.items[2][2] = c;
	return result;
}

Matrix create_rotation_y(float angle) {
	Matrix result = Matrix();
	angle = radians(angle);
	float c = cos(angle);
	float s = sin(angle);
	// set trig to be 0
	if(abs(c) < 0.0005f) { c = 0.0f; }
	if(abs(s) < 0.0005f) { c = 0.0f; }

	result.items[0][0] = c;
	result.items[0][2] = s;
	result.items[2][0] = -s;
	result.items[2][2] = c;
	return result;
}

Matrix create_rotation_z(float angle) {
	Matrix result = Matrix();
	angle = radians(angle);
	float c = cos(angle);
	float s = sin(angle);
	// set trig to be 0
	if(abs(c) < 0.0005f) { c = 0.0f; }
	if(abs(s) < 0.0005f) { c = 0.0f; }

	result.items[0][0] = c;
	result.items[0][1] = -s;
	result.items[1][0] = s;
	result.items[1][1] = c;
	return result;
}