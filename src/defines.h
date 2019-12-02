#ifndef defines_h
#define defines_h

#include "ANSI_include.h"

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



#endif /* defines_h */
