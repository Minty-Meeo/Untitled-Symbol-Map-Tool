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

struct symbol {
	unsigned int startAddr;
	unsigned int sizeOf;
	unsigned int virtualAddr;
	//	unsigned int optimizationLevel;
	string nameOf;
};

struct codeBlock {
	string nameOf;
	vector<unsigned int> virtualAddr;
	vector<string> ppcInstruction;
};

void readSymbolMap(vector<symbol>& mainVector);
void writeSymbolMap(const vector<symbol>& mainVector);
void readCodeMap(vector<codeBlock>& mainVector) {
	ifstream inFile;			// InFile Stream
	string dummy = "";				// Used to check for CODE BLOCK TITLES and other stuff
	inFile.open("testCode.txt");

	mainVector.resize(999);

	while (!(inFile.eof())) {	// Code Map --> Vector
		static int filePos = 0;
		static int blockCount = 0;
		static int lineCount = 0;

		filePos = inFile.tellg();					// Store file position temporarily
		cout << inFile.tellg() << " ";
		getline(inFile, dummy, '\n');				// Read line as string
		if (dummy[dummy.size() - 1] == ':') {		// If line is a CODE BLOCK TITLE
			blockCount++;								// Next index in codeMap vector
			lineCount = 0;								// Reset Line Count
			mainVector.resize(blockCount + 1);		// Allocate new CODE BLOCK

			mainVector[blockCount].nameOf = dummy;		// Store CODE BLOCK TITLE
			//cout << "GRABBED CODE BLOCK TITLE" << endl;	// [DEBUG]
			continue;
		}
		inFile.seekg(filePos);		// Restore file position.  Remainder of block only occurs if line is not a CODE BLOCK TITLE
		cout << inFile.tellg() << " ";


		mainVector[blockCount].virtualAddr.resize(lineCount + 1);		// Allocate new CODE LINE Virtual Address
		mainVector[blockCount].ppcInstruction.resize(lineCount + 1);	// Allocate new CODE LINE PPC Instruction

		inFile >> hex >> mainVector[blockCount].virtualAddr[lineCount] >> dec;		// Virtual Address
		inFile >> dummy;															// Ignore excessive Symbol Name
		getline(inFile, mainVector[blockCount].ppcInstruction[lineCount], '\n');	// Symbol Name

//		cout << mainVector[blockCount].virtualAddr[lineCount] << endl;		// [DEBUG]
//		cout << mainVector[blockCount].ppcInstruction[lineCount] << endl;		// [DEBUG]
		system("pause");

		lineCount++;		// Next index
	}
	cout << inFile.eof() << " ";
	inFile.close();
}

void readCodeMapRevised() {
	ifstream inFile;
	string dummy;
	int filePos;

	vector<codeBlock> mainVector(10);


	inFile.open("testCode.txt");



	while (!(inFile.eof())) {
		int blockCount = 0;

		mainVector.resize(blockCount + 1);					// Allocate +1 CODE BLOCK

		getline(inFile, mainVector[blockCount].nameOf, '\n');	// Read CODE BLOCK TITLE

		cout << mainVector[blockCount].nameOf << endl;			// [DEBUG]

		while (!(inFile.eof())) {
			int lineCount = 0;

			filePos = inFile.tellg();
			cout << inFile.tellg() << " ";

			inFile >> mainVector[blockCount].nameOf;
			cout << inFile.tellg() << " ";

			//			inFile.clear();
			inFile.seekg(filePos);
			cout << inFile.tellg() << " ";

			mainVector[blockCount].virtualAddr.resize(lineCount + 1);		// Allocate +1 CODE LINE
			mainVector[blockCount].ppcInstruction.resize(lineCount + 1);	// Allocate +1 CODE LINE

			inFile >> hex >> mainVector[blockCount].virtualAddr[lineCount];				// Read CODE LINE VIRTUAL ADDRESS
			inFile >> dummy;															// Read CODE LINE TITLE (unneeded)
			getline(inFile, mainVector[blockCount].ppcInstruction[lineCount], '\n');	// Read CODE LINE PPC INSTRUCTION

			cout << hex << mainVector[blockCount].virtualAddr[lineCount] << " ";		// [DEBUG]
			cout << mainVector[blockCount].ppcInstruction[lineCount] << endl;			// [DEBUG]

			lineCount++;
		}

		blockCount++;
	}
}

void writeCodeMap();

void testFunc() {
	string dummy;
	ifstream inFile;			// InFile Stream
//	int codeBlockCount = 0;		// [DEBUG] number of code blocks

	inFile.open("testCode.txt");

	getline(inFile, dummy, '\n');			// Read line as string
//	cout << dummy;
	cout << dummy[dummy.size() - 1];
	if (dummy[dummy.size() - 1] == ':') {		// If line is a CODE BLOCK TITLE
		cout << "haha lol";
	}

	inFile.close();
}

void testFunc2() {
	ifstream inFile;			// InFile Stream
	string dummy;				// Used to check for CODE BLOCK TITLES and other stuff
	inFile.open("testCode.txt");
	int filePos;
	while (!(inFile.eof())) {	// Code Map --> Vector

		filePos = inFile.tellg();					// Store file position temporarily
		cout << inFile.tellg() << " ";

		getline(inFile, dummy, '\n');				// Read line as string
		cout << dummy;

		//inFile.seekg(filePos);		// Restore file position.  Remainder of block only occurs if line is not a CODE BLOCK TITLE
		cout << inFile.tellg() << " ";

	}
	cout << inFile.eof() << " ";
}

int main() {
	vector<symbol> symbolMap;	// Vector containing entire section
	vector<codeBlock> codeMap;	// Vector containing entire Code Map (hopefully)

//	testFunc2();
	readCodeMapRevised();

	//	readCodeMap(codeMap);
	//	readSymbolMap(symbolMap);
	//	writeSymbolMap(symbolMap);



}

void readSymbolMap(vector<symbol>& mainVector) {
	ifstream inFile;			// InFile Stream
	string dummy;				// Used to check for UNUSED symbols
	int unusedSymbolCount = 0;	// [DEBUG] number of UNUSED symbols

	inFile.open("test.txt");

	while (!(inFile.eof())) {	// .MAP file --> Vector
		static int filePos;
		static int i = 0;

		filePos = inFile.tellg();	// Store file position temporarily
		inFile >> dummy;			// Read Starting Address as string
		if (dummy == "UNUSED") {	// If function is UNUSED,
			getline(inFile, dummy, '\n');				// skip its line
			cout << "SKIPPED UNUSED SYMBOL" << endl;	// [DEBUG]
			unusedSymbolCount++;						// [DEBUG]
			continue;
		}
		inFile.seekg(filePos);		// Restore file position.  Remainder of block only occurs if symbol is not UNUSED.

		mainVector.resize(mainVector.size() + 1);	// Allocate new index for mainVector vector

		inFile >> hex >> mainVector[i].startAddr >> dec;		// Starting Address
		inFile >> hex >> mainVector[i].sizeOf >> dec;		// Size
		inFile >> hex >> mainVector[i].virtualAddr >> dec;	// Virtual Address
		getline(inFile, mainVector[i].nameOf, '\n');		// Symbol Name
		cout << mainVector[i].nameOf << endl;		// [DEBUG]
		i++;		// Next index
	}

	cout << unusedSymbolCount << " unused symbols." << endl;		// [DEBUG]

	inFile.close();
}

void writeSymbolMap(const vector<symbol>& mainVector) {
	ofstream outFile;			// OutFile Stream

	outFile.open("output.txt");

	for (int i = 0; i <= (mainVector.size() - 1); i++) {	// Vector --> .MAP file
		outFile << "  ";
		outFile << setw(8) << right << hex << setfill('0') << mainVector[i].startAddr << " ";
		outFile << setw(6) << right << hex << setfill('0') << mainVector[i].sizeOf << " ";
		outFile << setw(8) << right << hex << setfill('0') << mainVector[i].virtualAddr;
		outFile << mainVector[i].nameOf;
		outFile << endl;
	}

	outFile.close();
}
