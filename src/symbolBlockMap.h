#ifndef symbolBlockMap_h
#define symbolBlockMap_h

#include "ANSI_include.h"
#include "defines.h"

void resizeSymbolBlock( vector<symbolBlock>& mainVector, string nameToLookFor, int amountToShift );
void makeSymbolBlockUsed( vector<symbolBlock>& mainVector, string nameToLookFor );
void realignSymbolBlockMap( vector<symbolBlock>& mainVector );
void trimUnusedSymbols( vector<symbolBlock>& mainVector );
void trimOverlapSymbols( vector<symbolBlock>& mainVector );

#endif /* symbolBlockMap_h */
