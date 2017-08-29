//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

// include(cstdlib) for: size_t
// include(cstdint) for: C99 standard types
#include <cstdlib>
#include <cstdint>

// include(vector) for: std::vector
#include <vector>
using std::vector;

// include(bitset) for: std::bitset
#include <bitset>
using std::bitset;

#include "KPartialSumsDebug.h"

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// all returned solutions (returned as BCI Coded Integer Value): have at least
// one bit set - or it would not be a solution ;-)
//
// thus we need a fast convenient way to convert each positive unsigned
// BCI Coded Integer Value to its set of Index Values:
//    BCI Coded (LSB) <<-->>  ZERO-Based [0] Index
//    BCI Coded (MSB) <<-->>  ZERO-Based [N-1] Index
//
// STD::BITSET does the trick here, initialized from unsigned integer
// quickly computes index values of bits set - although its very tempting
// to write cool bit-hack loops forever (and my first draft of both the
// encode and decode portions of this algorithm did just that), BITSET
// will be very much easier, faster, more API Capable, and less error
// prone (although probably not available on embedded platforms).
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

uint64_t
kPartialSums4 ( int *someArray , int targetSum )
{

   size_t N = 4;
   uint64_t retNumVals = 0u;
   uint64_t maxNum = 16u;

   cout << ">>> DEBUG: targetSum = [[ " << targetSum << " ]]" << endl;

   // count from 1 (not zero; the permutation {0,0,...0} is not feasible solution)
   // each count represents a series of bits set to "1"
   // *AND* counting in this way covers *ALL* permutations
   // each set of bits set represents a candidate permutation
   // find those bits and sum the values in the array at those bit positions

   for( uint64_t idx = 1u ; idx < maxNum ; ++idx )
   {
     int sumTval = 0;
     cout << ">>> DEBUG( kPartialSums4 ): outer loop counter = [[ " << idx << " ]]" << endl;
     cout << ">>> DEBUG( kPartialSums4 ): sumTval reset [[ " << sumTval << " ]]" << endl;

     for( size_t arrayIdx = 0 ; arrayIdx < N ; ++arrayIdx )
     {
         cout << ">>> --- DEBUG( kPartialSums4 ): inner loop counter = [[ " << arrayIdx << " ]]" << endl;
         cout << ">>> --- DEBUG( kPartialSums4 ): someArray["<<arrayIdx<<"] = [[ "<<someArray[arrayIdx]<<" ]]" << endl;
         if( idx & (1 << arrayIdx) ) {
            cout << ">>> ------- BIT INDEX MATCH: [[ " << idx << " || " << arrayIdx << " ]]" << endl;
            sumTval += someArray[ arrayIdx ];
         }
     }

     cout << ">>> --- TARGET SUM DEBUG: sumTval = [[ " << sumTval << " ]]" << endl;
     cout << ">>> --- TARGET SUM DEBUG: targetSum = [[ " << targetSum << " ]]" << endl;
     if( sumTval == targetSum )
     {
        cout << ">>> --- TARGET SUM MATCHED: [[]]" << endl;
        ++retNumVals;
        //retVals.push_back( idx );
     }
     else
     {
        cout << ">>> --- TARGET SUM NOT MATCHED: [[]]" << endl;
     }

   }
   return( retNumVals );
};


//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
// FILE-NAME: [["KPartialSums_FuncTemplate.h"]]
// [[ David Faris :: 2017-08-27 ]]
// Copyright (C) 2017 by David W. Faris, PhD
// This original code is placed into the public domain
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
