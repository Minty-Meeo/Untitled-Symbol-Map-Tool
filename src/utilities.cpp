#include "utilities.h"


void removeCarriageReturns(  ) {
	string inFileName = "GPVE01 text1.map";
	string outFileName = "testOutput.txt";
	
	ifstream inFile;
	inFile.open( inFileName.c_str(), std::ios::binary );
	ofstream outFile;
	outFile.open( outFileName.c_str(), std::ios::binary);
	
	char buffer;
		
	while (true) {
		inFile.get(buffer);					// Read Character
		if ( inFile.eof() )					// If there /isn't one/
			break;							// Cease immediately
		if ( buffer != '\r' )				// 
			outFile << std::hex << buffer;	// 

	}
	
	inFile.close();
	outFile.close();
}
		
//void getLineCRLF( ifstream& inFile, string& str ) {
//	getline( inFile, str, '\n' );
//	if ( str.back() == '\r' )
//		str.erase( str.size() );
//	if ( inFile.peek() == '\r' )
//		inFile.ignore(1);
//}

void ignoreAll( char ignoredChar, ifstream& inFile ) {
	while (true) {
		if (inFile.peek() == ignoredChar)
			inFile.ignore(1);
		else
			break;
	}
}

int asdf() {
	return 69;
}

unsigned int stringToHex( const char cstring[], unsigned int strLength ) {
	int accumulator = 0;	// Reset Accumulator
	strLength -= 1;			// Modify for Zero-Based Numbering

	for ( unsigned int i = 0; i <= strLength; i++ ) {
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
