#include <cstdint>
#include <cstdlib>
#include <cstddef>

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "KPartialSums.h"

template< typename T , size_t N , typename S >
uint64_t
kPartialSums2 (
   T (&someArray)[N] ,
   S targetSum ,
   std::vector<uint64_t>& retVals
)
{
   uint64_t retNumVals = 0u;
   uint64_t maxNum = (uint64_t)POW2(N);

   // count from 1 (not zero; the permutation {0,0,...0} is not feasible solution)
   // each count represents a series of bits set to "1"
   // *AND* counting in this way covers *ALL* permutations
   // each set of bits set represents a candidate permutation
   // find those bits and sum the values in the array at those bit positions
   for( uint64_t idx = 1u ; idx < maxNum ; ++idx ) {
     T sumTval = 0;
     for( size_t arrayIdx = 0 ; arrayIdx < N ; ++arrayIdx ) {
		 if( idx & (1ull << arrayIdx) ) {  sumTval += someArray[ arrayIdx ]; }
	 }
	 if( sumTval == targetSum ) { retVals.push_back( idx ); }
   }
   return( retNumVals );
};

int
main( int argc , char* argv[] ) {
   cout << endl;
   cout << "*** [[ K-PARTIAL-SUMS ]] ***" << endl;

   uint64_t numMatches  =  0u;
   std::vector<uint64_t> retVals;
   uint64_t fubar[ 4 ] = { 5ul , 5ul , 15ul , 10ul };

   numMatches  =  kPartialSums2( fubar , 15ul , retVals );
   cout << "EXAMPLE 1:  numMatches = [[ " << numMatches << " ]]" << endl;

//kPartialSums (
//   const T (&someArray)[N] ,
//   const S targetSum ,
//   std::vector<uint64_t>& retVals );

   cout << "*** [[ K-PARTIAL-SUMS ]] *** DONE" << endl;
   cout << endl;
   return( EXIT_SUCCESS );
}
