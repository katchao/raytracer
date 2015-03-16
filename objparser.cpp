#include "objparser.h"

/*OBJ Parser.*/

/* 'v'  signifies a vertex so make all the verticies
*  'vt' texture coordinate of one vertex
*  'vn' the normal of the vertex
*  'f'  is a face
*         	- 3 groups of 3 numbers ##/##/##
		  	- each ##/##/## describes a vertex
		  		- 01/##/## says the index in the line vertex to use. (indexing starts with 1 and NOT 0) - 3 floats
		  		- ##/02/## says the texture coord to use 2 floats
		  		- ##/##/03 says the normal to use for this vertex

*  Plan of attack : go through each line and save all the verts in an array <vector>
					- save all the normals in a separate array <vector>
					- go throught the f lines and assign the normals to each vertex
					- make a local Geo. pos = verts[f[0] - 1] 
										normal = normals[f[2] - 1]
*/
ObjParser::ObjParser() {
}

ObjParser::ObjParser(string ifile) {
	file = ifile;
}

vector<Primitive*> ObjParser::parse() {
	vector<Primitive*>  triangles; 

	/*
	ifstream infile;
	infile.open(file);
	const int num_line_chars = 50;
//cout << "Open file a second time.\n";
	string linecontents;
	char currLine[256];
	int numLines;
	if (!infile.good()) {
		cout << "Error Reading File :/ Sucks to be you.\n";
		
	} else {
		while (!infile.eof()) {
		//Grab the first line
		getline(infile, linecontents);		
		
		// If a vertex and not a normal or texture coordinate
		if ((linecontents[0] == 'v') && (linecontents[1] == ' ')) {
			vector<float> vertex;
			string currflt = "";
			for(int i=2; i<linecontents.size();i++) { // ignore the v

				if (linecontents[i] == ' ') {
					try {
						vertex.push_back(atof(currflt.c_str()));
					} catch (int e) {
						continue;
					}
			 		currflt = "";
				} else {
					currflt.push_back(linecontents[i]);
				}
			}
			//cout << "last Elem = " << currflt << endl;
			vertex.push_back(atof(currflt.c_str()));// this gets the last element
			cout << "Vertex " << verticies.size() + 1 << ": ( " << vertex[0] << ", " << vertex[1] << ", " << vertex[2] << ")" << endl;
			verticies.push_back(vertex);

		// if a face
		} else if (linecontents[0] == 'f') {

			vector<vector<float> > face; // holds the verticies
			string currflt = "";
			for(int i=2; i<linecontents.size();i++) { // ignore the f char

				//ignore the values for textures and normals
				if (linecontents[i] == '/') {
					
					try {
						int index = atoi(currflt.c_str()) - 1;
						face.push_back(verticies[index]);
					} catch (int e) {
					}
					
					//skip to the next white space
					while(linecontents[i] != ' ') {
						i++;
					}
					//reset the current string
			 		currflt = "";
				
			 	//If this is the value that we want
				} else if (linecontents[i] == ' ') {
					try {
						int index = atoi(currflt.c_str()) - 1;
						face.push_back(verticies[index]);
					} catch (int e) {
					}
			 		currflt = "";

				} else {
					currflt.push_back(linecontents[i]);
				}
			}
			
			// Adding the last vertex to the current face vector
			try {
				int index = atoi(currflt.c_str()) - 1;
				face.push_back(verticies[index]);// this gets the last element
			} catch (int e) {			
			}

			//push this face to the list of faces
			Vector vert1 = Vector(); vert1.x = face[0][0]; vert1.y = face[0][1]; vert1.z = face[0][2];
			Vector vert2 = Vector(); vert2.x = face[1][0]; vert2.y = face[1][1]; vert2.z = face[1][2];
			Vector vert3 = Vector(); vert3.x = face[2][0]; vert3.y = face[2][1]; vert3.z = face[2][2];
			Triangle triangle = Triangle(vert1, vert2, vert3);
			triangles.push_back(&triangle);
			//faces.push_back(face);

			cout << endl;
			cout << "Triangle " << triangles.size() << ": " << endl;
//			for(int k = 0; k<.size(); k++) {
			cout << "Vertex Num 1" << " : (" << triangle.v1.x << ", " << triangle.v1.y << ", " << triangle.v1.z << ")" << endl;
			cout << "Vertex Num 2" << " : (" << triangle.v2.x << ", " << triangle.v2.y << ", " << triangle.v2.z << ")" << endl;
			cout << "Vertex Num 3" << " : (" << triangle.v3.x << ", " << triangle.v3.y << ", " << triangle.v3.z << ")" << endl;
			//}
		}
	}
	}
	// while not end of file
	infile.close();
	cout << "Total Number of Triangles = " << triangles.size() << endl;
	cout << "I get there homie." << endl;
	*/
	return triangles;
}

