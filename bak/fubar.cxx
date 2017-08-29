uint64_t
kPartialSums4 ( int *someArray , int targetSum )
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
