#include "test.h"
#include "utilities.cpp"

void readSymbolMap(vector<symbolBlock>& mainVector);
void writeSymbolMap(const vector<symbolBlock>& mainVector);

// ====================================================================================================

void readSymbolMap(vector<symbolBlock>& mainVector) {	// .MAP file --> Vector

	ifstream inFile;			// InFile Stream
	int filePos;				// File position backup
	string strDummy;			// Used to check for UNUSED symbols
	int alignmentSizeDummy;			// Temporary Optimization Level holder

	inFile.open( inFileName.c_str(), std::ios::binary );

	int blockCount = 0;
	
	while ( !( inFile.eof() ) ) {
		
		mainVector.resize( mainVector.size() + 1 );			// Allocate +1 Symbol Block
		
		ignoreAll( ' ', inFile );
		
		filePos = inFile.tellg();							// Store file position temporarily
		inFile >> strDummy;									// Check if Starting Address says "UNUSED"
		inFile.seekg( filePos );							// Restore file position
		
		if ( strDummy == "UNUSED" ) {							// If function is UNUSED,

			mainVector[blockCount].startAddr = 0;					// Starting Address
			inFile.ignore(8);										// 
			ignoreAll( ' ', inFile );								// ' '
			
			inFile >> std::hex >> mainVector[blockCount].sizeOf;	// Size
			ignoreAll( ' ', inFile );								// ' '
			
			mainVector[blockCount].virtualAddr = 0;					// Virtual Address
			inFile.ignore(8);										// 
			ignoreAll( ' ', inFile );								// ' '
			
			mainVector[blockCount].alignmentSize = 0;				// Alignment Size
			
			getline( inFile, mainVector[blockCount].nameOf, '\n' );	// Name
			
			mainVector[blockCount].unusedFlag = true;

		} else {
			
			inFile >> std::hex >> mainVector[blockCount].startAddr;		// Starting Address
			ignoreAll( ' ', inFile );									// ' '
			
			inFile >> std::hex >> mainVector[blockCount].sizeOf;		// Size
			ignoreAll( ' ', inFile );									// ' '
			
			inFile >> std::hex >> mainVector[blockCount].virtualAddr;	// Virtual Address
			ignoreAll( ' ', inFile );									// ' ' or '  '
			
			filePos = inFile.tellg();									// Store file position temporarily
			alignmentSizeDummy = 0;										// Reset alignmentSizeDummy
			inFile >> std::dec >> alignmentSizeDummy;							// Attempt to read an Alignment Size
			if ( alignmentSizeDummy != 0 ) {									// If the Alignment Size is valid
				mainVector[blockCount].alignmentSize = alignmentSizeDummy;	 	// Store it
				ignoreAll( ' ', inFile );									// ' '
			} else {														// else
				inFile.clear();												// Clear error bit from improper read
				inFile.seekg(filePos);										// Restore file position.  This symbol has no Alignment Size
			}
			
			getline( inFile, mainVector[blockCount].nameOf, '\n' );		// Symbol Name
			
			mainVector[blockCount].unusedFlag = false;
			
		}
		
//		std::cout << mainVector[blockCount].nameOf << std::endl;	// [DEBUG]
		
		blockCount++;		// Next index
		
		inFile.peek();		// Check for EOF
		
	}

	inFile.close();
	
}

void writeSymbolMap(const vector<symbolBlock>& mainVector) {	// Vector --> .MAP file
	
	ofstream outFile;			// OutFile Stream

	outFile.open( outFileName.c_str() );
	
	std::cout ;

	for (int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
	
		if ( mainVector[blockCount].unusedFlag == true ) {
			
//			outFile << "  ";
//			outFile << "UNUSED  " << " ";
//			outFile << std::hex << std::right << std::setfill('0') << std::setw(6) << mainVector[blockCount].sizeOf    << " ";		// Size
//			outFile << "........" << " ";
//			outFile << mainVector[blockCount].nameOf;
//			outFile << '\n';
			
		} else {
			
			outFile << "  ";
			outFile << std::hex << std::right << std::setfill('0') << std::setw(8) << mainVector[blockCount].startAddr << " ";		// Starting Address
			outFile << std::hex << std::right << std::setfill('0') << std::setw(6) << mainVector[blockCount].sizeOf    << " ";		// Size
			outFile << std::hex << std::right << std::setfill('0') << std::setw(8) << mainVector[blockCount].virtualAddr << " ";	// Virtual Address
			if ( mainVector[blockCount].alignmentSize != 0 )																				// If present...
				outFile << " " << std::dec << mainVector[blockCount].alignmentSize << " ";													// Optimization Level
			outFile << mainVector[blockCount].nameOf;																				// Name
			outFile << '\n';
			
		}
	
	}

	outFile.close();
	
}
