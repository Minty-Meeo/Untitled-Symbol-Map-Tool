#include "codeMap.h"

#include "utilities.h"

const unsigned int readBlockTitleLength = 30;
unsigned int writeBlockTitleLength = 30;

void readCodeMap(vector<symbolBlock>& mainVector) {
	string inFileName = "GPVE01 text1.map";
	string outFileName = "testOutput.txt";
	
	ifstream inFile;
	string dummy;
	std::streampos filePos;

	inFile.open( inFileName.c_str(), std::ios::binary );
	int blockCount = 0;
	int lineCount = 0;
	
	while ( !( inFile.eof() ) ) {
		
		mainVector.resize( blockCount + 1 );					// Allocate +1 CODE BLOCK
		
		getline( inFile, mainVector[blockCount].nameOf, '\n' );								// Read CODE BLOCK Title
		mainVector[blockCount].nameOf.erase( mainVector[blockCount].nameOf.size() - 1 );	// Remove ':' character from CODE BLOCK Title
//		std::cout << mainVector[blockCount].nameOf << ':' << std::endl;						// [DEBUG]
		
		while ( !( inFile.eof() ) ) {
			
			if (inFile.peek() == '\n' || inFile.peek() == '/' ) {	// If it encounters another newline, that means a block has ended!!  Alternatively, a "beginning of" note also ends a block.
				mainVector[blockCount].sizeOf = lineCount * 4;	// Calculate block size
				lineCount = 0;									// Reset lineCount
				break;											// Escape to higher loop
			}
			
			mainVector[blockCount].ppcInstruction.resize( lineCount + 1 );	// Allocate PPC Instruction
			
			if ( lineCount == 0 ) {											// Only read the first Virtual Address, since that's all we really need.  Optimization!!
				inFile >> std::hex >> mainVector[blockCount].virtualAddr;		// Read CODE LINE VIRTUAL ADDRESS to vector
				inFile.ignore(1);												// Eliminate whitespace
			} else {
				inFile.ignore(8);												// Ignore CODE LINE Virtual Address
				inFile.ignore(1);												// Eliminate whitespace
			}
			inFile.ignore(readBlockTitleLength);							// Ignore CODE BLOCK TITLE within CODE LINE
			inFile.ignore(1);												// Eliminate whitespace
			getline( inFile, mainVector[blockCount].ppcInstruction[lineCount], '\n');	// Read CODE LINE PPC INSTRUCTION
			
//			std::cout << std::hex << mainVector[blockCount].virtualAddr + ( lineCount * 4 ) << " ";		// [DEBUG]
//			std::cout << mainVector[blockCount].nameOf.substr( 0, writeBlockTitleLength ) << " ";
//			for (int i = ( writeBlockTitleLength - mainVector[blockCount].nameOf.size()); i > 0; i-- )	// [DEBUG]
//				std::cout << ' ';
//			std::cout << mainVector[blockCount].ppcInstruction[lineCount] << std::endl;					// [DEBUG]
			
			lineCount++;
			
		}
		

		
		blockCount++;
		
		while ( inFile.peek() == '/' ) {		// Eliminate "beginning of" comments.  IDK how to save them.
			inFile.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		}
		ignoreAll( '\n', inFile );	// Eliminate extra newline
//		std::cout << std::endl;			// [DEBUG]
		
	}
}

void writeCodeMap(const vector<symbolBlock>& mainVector) {
	string inFileName = "GPVE01 text1.map";
	string outFileName = "testOutput.txt";
	
	ofstream outFile;			// OutFile Stream
	
	outFile.open( outFileName.c_str() );
	
	for (unsigned int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++) {	// Vector --> Code Map
		outFile << mainVector[blockCount].nameOf << ':' << std::endl;													// CODE BLOCK Title
		for (unsigned int lineCount = 0; lineCount <= ( mainVector[blockCount].ppcInstruction.size() - 1 ); lineCount++ ) {
//			outFile << std::hex << mainVector[blockCount].virtualAddr + (lineCount * 4) << " ";								// CODE LINE Virtual Address
//			outFile << mainVector[blockCount].nameOf.substr( 0, writeBlockTitleLength ) << " ";								// CODE LINE Title within CODE LINE
//			for (int i = ( writeBlockTitleLength - mainVector[blockCount].nameOf.size()); i > 0; i-- )						// Fill remaining 30 characters with whitespace when needed.
//				outFile << ' ';
			outFile << mainVector[blockCount].ppcInstruction[lineCount];												// CODE LINE PPC Instruction
			outFile << std::endl;
		}
		outFile << std::endl;																							// Newline seperating CODE BLOCKs
	}

	outFile.close();
}
