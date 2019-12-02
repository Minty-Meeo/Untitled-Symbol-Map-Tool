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

unsigned int stringToHex( const char cstring[], unsigned int strLength );
unsigned int asciiToInt( char asciiChar );

struct symbol {
	unsigned int startAddr;
	unsigned int sizeOf;
	unsigned int virtualAddr;
//	unsigned int optimizationLevel;
	string nameOf;
//	string member;
//	string object;
//	string source;
};

int main() {
	vector<symbol> symbolMap;	// Vector containing entire section
	ifstream inFile;			// InFile Stream
	ofstream outFile;			// OutFile Stream
	string dummy;				// Used to check for UNUSED symbols
	int unusedSymbolCount = 0;	// [DEBUG] number of UNUSED symbols


	inFile.open( "test.txt" );

	while ( !( inFile.eof() ) ) {	// .MAP file --> Vector
		static int filePos;
		static int i = 0;

		filePos = inFile.tellg();	// Store file position temporarily
		inFile >> dummy;			// Read Starting Address as string
		if ( dummy == "UNUSED" ) {	// If function is UNUSED,
			getline( inFile, dummy, '\n' );				// skip its line
			cout << "SKIPPED UNUSED SYMBOL" << endl;	// [DEBUG]
			unusedSymbolCount++;						// [DEBUG]
			continue;
		}
		inFile.seekg(filePos);		// Restore file position.  Remainder of block only occurs if symbol is not UNUSED.

		symbolMap.resize( symbolMap.size() + 1 );	// Allocate new index for symbolMap vector

		inFile >> hex >> symbolMap[i].startAddr >> dec;		// Starting Address
		inFile >> hex >> symbolMap[i].sizeOf >> dec;		// Size
		inFile >> hex >> symbolMap[i].virtualAddr >> dec;	// Virtual Address
		getline( inFile, symbolMap[i].nameOf, '\n' );		// Symbol Name
		cout << symbolMap[i].nameOf << endl;		// [DEBUG]
		i++;		// Next index
	}

	cout << unusedSymbolCount << " unused symbols." << endl;		// [DEBUG]

	inFile.close();

	outFile.open( "output.txt" );

	for (int i = 0; i <= ( symbolMap.size() - 1 ); i++ ) {	// Vector --> .MAP file
		outFile << "  ";
		outFile << setw(8) << right << hex << setfill('0') << symbolMap[i].startAddr << " ";
		outFile << setw(6) << right << hex << setfill('0') << symbolMap[i].sizeOf << " ";
		outFile << setw(8) << right << hex << setfill('0') << symbolMap[i].virtualAddr;
		outFile << symbolMap[i].nameOf;
		outFile << endl;
	}

	outFile.close();
}

unsigned int stringToHex( const char cstring[], unsigned int strLength ) {
	int accumulator = 0;	// Reset Accumulator
	strLength -= 1;			// Modify for Zero-Based Numbering

	for ( int i = 0; i <= strLength; i++ ) {
		accumulator
			+= ( asciiToInt( cstring[ strLength - i ] )		// Convert ASCII character to real hexadecimal.
			* pow( 16, i ));								// Multiply real hexadecimal to match digit place.
	}

	return accumulator;
}

unsigned int asciiToInt( char asciiChar ) {
	switch ( asciiChar ) {
		case '0':
			return 0x0;
		case '1':
			return 0x1;
		case '2':
			return 0x2;
		case '3':
			return 0x3;
		case '4':
			return 0x4;
		case '5':
			return 0x5;
		case '6':
			return 0x6;
		case '7':
			return 0x7;
		case '8':
			return 0x8;
		case '9':
			return 0x9;
		case 'A': case 'a':
			return 0xA;
		case 'B': case 'b':
			return 0xB;
		case 'C': case 'c':
			return 0xC;
		case 'D': case 'd':
			return 0xD;
		case 'E': case 'e':
			return 0xE;
		case 'F': case 'f':
			return 0xF;
		default:	// Input is not in the hexadecimal character set!!
			return 5318008;
	}
}
