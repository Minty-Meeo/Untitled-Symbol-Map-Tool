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
	vector<symbol> symbolMap;
	char buffer[256];
	char dummy[256];
	string temp;
	ifstream inFile;
	ofstream outFile;
	int asdf;


	inFile.open( "test.txt" );



	while ( !( inFile.eof() ) ) {	// .MAP file --> Vector
		static int i = 0;
		//==============================
		// STARTING ADDRESS
		//==============================
		inFile >> buffer;
		temp = buffer;
		if ( temp == "UNUSED" ) {	// If function is unused, skip its line.
			inFile >> dummy;
			inFile >> dummy;
			inFile >> dummy;
			inFile >> dummy;
			inFile >> dummy;
			cout << "SKIPPED UNUSED SYMBOL" << endl << endl;
			continue;
		}

		symbolMap.resize( symbolMap.size() + 1 );	// Allocate new index for symbolMap vector (only happens when needed!)

		symbolMap[i].startAddr = stringToHex( buffer, 8 );
		cout << symbolMap[i].startAddr << " ";
		//==============================
		// SIZE OF
		//==============================
		inFile >> hex >> symbolMap[i].sizeOf >> dec;
		//inFile >> buffer;
		//symbolMap[i].sizeOf = stringToHex( buffer, 6 );
		cout << symbolMap[i].sizeOf << " ";
		//==============================
		// VIRTUAL ADDRESS
		//==============================
		inFile >> hex >> symbolMap[i].virtualAddr >> dec;
		//inFile >> buffer;
		//symbolMap[i].virtualAddr = stringToHex( buffer, 8 );
		cout << symbolMap[i].virtualAddr << " ";
		//==============================
		// NAME OF
		//==============================
		getline( inFile, symbolMap[i].nameOf, '\n' );		// reads up to newline, all things intact.
		cout << symbolMap[i].nameOf << " ";


		cout << endl << endl;
		i++;		// Next index
	}

	inFile.close();

	outFile.open( "output.txt" );

	for (int i = 0; i <= ( symbolMap.size() - 1 ); i++ ) {
		outFile << "  ";
		outFile << setw(8) << right << hex << setfill('0') << symbolMap[i].startAddr << " ";
		outFile << setw(6) << right << hex << setfill('0') <<symbolMap[i].sizeOf << " ";
		outFile << setw(8) << right << hex << setfill('0') <<symbolMap[i].virtualAddr;
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
