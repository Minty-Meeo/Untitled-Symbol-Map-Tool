#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <cmath>
#include <cstring>
#include <limits>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

#ifndef test_h
#define test_h

struct symbolBlock {
	unsigned int startAddr;
	unsigned int sizeOf;
	unsigned int virtualAddr;
	unsigned int oLevel;	// Remove this!!
	unsigned int alignmentSize;
	string nameOf;
	vector<string> ppcInstruction;
	
	bool unusedFlag;

};

string inFileName = "GPVE01 text1.map";
string outFileName = "testOutput.txt";

#endif /* test_h */


