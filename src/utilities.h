#ifndef utilities_h
#define utilities_h

#include "ANSI_include.h"
#include "defines.h"

void removeCarriageReturns(  );
//void getLineCRLF( ifstream& inFile, string& str );
void ignoreAll( char ignoredChar, ifstream& inFile );
int asdf();
unsigned int stringToHex( const char cstring[], unsigned int strLength );
unsigned int asciiToInt( char asciiChar );

#endif /* utilities.h */
