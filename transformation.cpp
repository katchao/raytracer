#include "transformation.h"

Transformation::Transformation() {
	m = Matrix();
	minvt = Matrix();
}

Transformation::Transformation(Matrix m1) {
	m = m1;
	minvt = inverse(m);
}

Vector Transformation::transform_dir(Vector v) {
	// need help, will the result be a 1x4 vector or 1x3 vector? since currently the vector class only supports 1x3 vectors
	Vector result = vector_multiply(minvt, v);
	result.w = 0.0f;
	return result;
}

Vector Transformation::transform_pos(Vector v) {
	// need help, will the result be a 1x4 vector or 1x3 vector? since currently the vector class only supports 1x3 vectors
	Vector result = vector_multiply(minvt, v);
	result.w = 1.0f;

	cout << "Point \n";
	result.print();
	return result;
}

Vector Transformation::transform_normal(Vector v) {
	Matrix invTrans = minvt;
	invTrans.transpose();
	Vector result = vector_multiply(invTrans, v);
	cout << endl;
	cout << "Normal vector \n";
	result.print();
	return result;
}

Vector Transformation::vector_multiply(Matrix m, Vector v) {
	Vector result = Vector();
	result.x = m.items[0][0]*v.x + m.items[0][1]*v.y + m.items[0][2]*v.z + m.items[0][3]*v.w;
	result.y = m.items[1][0]*v.x + m.items[1][1]*v.y + m.items[1][2]*v.z + m.items[1][3]*v.w;
	result.z = m.items[2][0]*v.x + m.items[2][1]*v.y + m.items[2][2]*v.z + m.items[2][3]*v.w;
	result.w = m.items[3][0]*v.x + m.items[3][1]*v.y + m.items[3][2]*v.z + m.items[3][3]*v.w;
	return result;
}

Matrix Transformation::inverse(Matrix m) {
	Matrix result = Matrix();
	// 
	float a11 = m.items[0][0]; float a12 = m.items[1][0]; float a13 = m.items[2][0]; float a14 = m.items[3][0];
	float a21 = m.items[0][1]; float a22 = m.items[1][1]; float a23 = m.items[2][1]; float a24 = m.items[3][1];
	float a31 = m.items[0][2]; float a32 = m.items[1][2]; float a33 = m.items[2][2]; float a34 = m.items[3][2];
	float a41 = m.items[0][3]; float a42 = m.items[1][3]; float a43 = m.items[2][3]; float a44 = m.items[3][3];
	// Determinant
	// cout << a11 << ", "; cout << a12 << ", "; cout << a13 << ", "; cout << a14 << endl;
	// cout << a21 << ", "; cout << a22 << ", "; cout << a23 << ", "; cout << a24 << endl;
	// cout << a31 << ", "; cout << a32 << ", "; cout << a33 << ", "; cout << a34 << endl;
	// cout << a41 << ", "; cout << a42 << ", "; cout << a43 << ", "; cout << a44 << endl;
	// cout << endl;
	
	double det = a11*a22*a33*a44 + a11*a23*a34*a42 + a11*a24*a32*a43
			  + a12*a21*a34*a43 + a12*a23*a31*a44 + a12*a24*a33*a41
			  + a13*a21*a32*a44 + a13*a22*a34*a41 + a13*a24*a31*a42
			  + a14*a21*a33*a42 + a14*a22*a31*a43 + a14*a23*a32*a41
			  - a11*a22*a34*a43 - a11*a23*a32*a44 - a11*a24*a33*a42
			  - a12*a21*a33*a44 - a12*a23*a34*a41 - a12*a24*a31*a43
			  - a13*a21*a34*a42 - a13*a22*a31*a44 - a13*a24*a32*a41
			  - a14*a21*a32*a43 - a14*a22*a33*a41 - a14*a23*a31*a42;
	cout << "Determinant = " << det << endl;
	if (det != 0){
		setprecision(4);
		double D = 1.0f/det;
		cout << "1/det" << D << endl;
		float b11 = a22*a33*a44 + a23*a34*a42 + a24*a32*a43 - a22*a34*a43 - a23*a32*a44 - a24*a33*a42;
		float b12 = a12*a34*a43 + a13*a32*a44 + a14*a33*a42 - a12*a33*a44 - a13*a34*a42 - a14*a32*a43;
		float b13 = a12*a23*a44 + a13*a24*a42 + a14*a22*a43 - a12*a24*a43 - a13*a22*a44 - a14*a23*a42;
		float b14 = a12*a24*a33 + a13*a22*a34 + a14*a23*a32 - a12*a23*a34 - a13*a24*a32 - a14*a22*a33;
		float b21 = a21*a34*a43 + a23*a31*a44 + a24*a33*a41 - a21*a33*a44 - a23*a34*a41 - a24*a31*a43;
		float b22 = a11*a33*a44 + a13*a34*a41 + a14*a31*a43 - a11*a34*a43 - a13*a31*a44 - a14*a33*a41;
		float b23 = a11*a24*a43 + a13*a21*a44 + a14*a23*a41 - a11*a23*a44 - a13*a24*a41 - a14*a21*a43;
		float b24 = a11*a23*a34 + a13*a24*a31 + a14*a21*a33 - a11*a24*a33 - a13*a21*a34 - a14*a23*a31;
		float b31 = a21*a32*a44 + a22*a34*a41 + a24*a31*a42 - a21*a34*a42 - a22*a31*a44 - a24*a32*a41;
		float b32 = a11*a34*a42 + a12*a31*a44 + a14*a32*a41 - a11*a32*a44 - a12*a34*a41 - a14*a31*a42;
		float b33 = a11*a22*a44 + a12*a24*a41 + a14*a21*a42 - a11*a24*a42 - a12*a21*a44 - a14*a22*a41;
		float b34 = a11*a24*a32 + a12*a21*a34 + a14*a22*a31 - a11*a22*a34 - a12*a24*a31 - a14*a21*a32;
		float b41 = a21*a33*a42 + a22*a31*a43 + a23*a32*a41 - a21*a32*a43 - a22*a33*a41 - a23*a31*a42; 
		float b42 = a11*a32*a43 + a12*a33*a41 + a13*a31*a42 - a11*a33*a42 - a12*a31*a43 - a13*a32*a41;
		float b43 = a11*a23*a42 + a12*a21*a43 + a13*a22*a41 - a11*a22*a43 - a12*a23*a41 - a13*a21*a42;
		float b44 = a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a11*a23*a32 - a12*a21*a33 - a13*a22*a31;
		
		result.items[0][0] = b11*D; result.items[1][0] = b12*D; result.items[2][0] = b13*D; result.items[3][0] = b14*D;
		result.items[0][1] = b21*D; result.items[1][1] = b22*D; result.items[2][1] = b23*D; result.items[3][1] = b24*D;
		result.items[0][2] = b31*D; result.items[1][2] = b32*D; result.items[2][2] = b33*D; result.items[3][2] = b34*D;
		result.items[0][3] = b41*D; result.items[1][3] = b42*D; result.items[2][3] = b43*D; result.items[3][3] = b44*D;
		cout << "The Inverse Matrix\n";
		result.print();
		cout << " Elem[3][0] = " << result.items[0][3] << endl;

	} else {
		cout << "Determinant was 0\n";
	}
	return result;
}
// if it's a direction, the w is 0
// if it's a position, the w is 1
