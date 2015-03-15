#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstring>
#include "vector.h"



using namespace std;

class ObjParser {
public:
	vector<vector<float> > verticies;
	vector<vector<vector<float> > > faces;
	string file;
	ObjParser();
	ObjParser(string);
	void parse();

};

#endif
