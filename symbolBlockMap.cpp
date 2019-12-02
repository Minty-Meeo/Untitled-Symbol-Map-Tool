#include "test.h"
#include "utilities.cpp"


resizeSymbolBlock( vector<symbolBlock>& mainVector, string nameToLookFor, int amountToShift ) {
	
	bool foundAddressFlag = false;
	
	for ( int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
		if ( mainVector[blockCount].unusedFlag == false ) {
			switch (foundAddressFlag) {
			
				case true:		// Shift everything following resized Symbol Block
					mainVector[blockCount].startAddr += amountToShift;
					mainVector[blockCount].virtualAddr += amountToShift;
					break;
					
				case false:		// Resize Symbol Block
					if ( mainVector[blockCount].nameOf == nameToLookFor ) {
						foundAddressFlag = true;
						
						mainVector[blockCount].sizeOf += amountToShift;
					}
					break;
				
			}
		}
		
	}
	
	if ( foundAddressFlag == false )
		std::cout << "Warning: Symbol Block not found!" << std::endl;
	
}
	
makeSymbolBlockUsed( vector<symbolBlock>& mainVector, string nameToLookFor ) {
	
	bool foundAddressFlag = false;
	unsigned int amountToShift;
	
	for ( int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
	
		switch (foundAddressFlag) {
		
			case true:		// Shift everything following Symbol Block made used
				mainVector[blockCount].startAddr += amountToShift;
				mainVector[blockCount].virtualAddr += amountToShift;
				break;
				
			case false:		// Make Symbol Block used
				if ( mainVector[blockCount].nameOf == nameToLookFor ) {
					
					foundAddressFlag = true;
					amountToShift = mainVector[blockCount].sizeOf;
					
					mainVector[blockCount].startAddr = ( mainVector[blockCount - 1].startAddr + mainVector[blockCount - 1].sizeOf );		// Put Starting Address after previous Symbol Block
					mainVector[blockCount].virtualAddr = ( mainVector[blockCount - 1].virtualAddr + mainVector[blockCount - 1].sizeOf );	// Put Virtual Address after previous Symbol Block
					mainVector[blockCount].unusedFlag = false;
					
				}
				break;
			
		}
		
	}
	
	if ( foundAddressFlag == false )
		std::cout << "Warning: Symbol Block not found!" << std::endl;
}

realignSymbolBlockMap( vector<symbolBlock>& mainVector ) {
	
	int difference;
	unsigned int previousStartingBack;
	unsigned int previousVirtualBack;
	
	for ( int blockCount = 1; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
		
		difference = 0;
		
		previousStartingBack = mainVector[blockCount - 1].startAddr + mainVector[blockCount - 1].sizeOf;						// Calculate probable new Starting Address
		previousVirtualBack = mainVector[blockCount - 1].virtualAddr + mainVector[blockCount - 1].sizeOf;						// Calculate probable new Virtual Address
		
		if ( mainVector[blockCount].alignmentSize != 0 ) {																			// If the Symbol Block has an Alignment Size
			
			if ( ( previousStartingBack % mainVector[blockCount].alignmentSize ) != 0 ) {												// If the Symbol Block is not already aligned
				difference = ( mainVector[blockCount].alignmentSize - ( previousStartingBack % mainVector[blockCount].alignmentSize ) );	// Calculate how many bytes until alignment
				
			}
		
		}
		
		mainVector[blockCount].startAddr = previousStartingBack + difference;													// Assign new Starting Address
		mainVector[blockCount].virtualAddr = previousVirtualBack + difference;													// Assign new Virtual Address
		
	}

}

trimUnusedSymbols( vector<symbolBlock>& mainVector ) {

	for ( int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
		
		if ( mainVector[blockCount].unusedFlag == true ) {
			
			mainVector.erase( mainVector.begin() + blockCount );
			blockCount--;
			
		}
		
	}

}

trimOverlapSymbols( vector<symbolBlock>& mainVector ) {

	for ( int blockCount = 0; blockCount <= ( mainVector.size() - 1 ); blockCount++ ) {
		
		if ( mainVector[blockCount].alignmentSize == 1 ) {
			
			mainVector.erase( mainVector.begin() + blockCount );
			blockCount--;
			
		}
		
	}

}
