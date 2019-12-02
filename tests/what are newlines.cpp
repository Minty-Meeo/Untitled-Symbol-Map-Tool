#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <cmath>
#include <cstring>

using namespace std;

int main() {
	ifstream inFile;
	string asdf;
	streampos filePos;
	unsigned int hexadecimal;
	
	inFile.open( "testCode.txt", ios::in | ios::binary );
	
	cout << hex;
	
	cout << inFile.tellg();
	inFile >> asdf;
	cout << asdf << endl;
	
	cout << inFile.tellg();
	inFile >> asdf;
	cout << asdf << endl;
	
	cout << inFile.tellg();
	filePos = inFile.tellg();
	getline( inFile, asdf, '\n');
	cout << inFile.gcount();
	inFile.seekg(filePos, ios::beg);
	
	cout << inFile.tellg();
	inFile >> asdf;															// Read CODE LINE TITLE (unneeded)
	cout << asdf << endl;
	
	cout << inFile.tellg();
	getline( inFile, asdf, '\n');	// Read CODE LINE PPC INSTRUCTION
	cout << asdf << endl << endl;
}
