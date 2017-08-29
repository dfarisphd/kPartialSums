#include <cstddef>
#include <cstdint>

#include <iostream>
using std::cout;
using std::endl;

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
            cout << ">>> ------- DEBUG( kPartialSums4 ): binary integers ..." << endl;
            cout << ">>> ------- DEBUG idx = [1,2**N)  vice  arrayIdx = [0,N)" << endl;
            cout << ">>> ------- [[ ";
               std::cout.write(reinterpret_cast<const char*>(&idx), sizeof idx);
            cout << " , ";
               std::cout.write(reinterpret_cast<const char*>(&arrayIdx), sizeof arrayIdx);
            cout << " ]]" << endl;
         if( idx & (1 << arrayIdx) ) {
            cout << ">>> ------- MATCHED: [[]]" << endl;
            cout << ">>> ------- DEBUG: sumTval = [[ " << sumTval << " ]]" << endl;
            cout << ">>> ------- DEBUG: someArray["<<arrayIdx<<"] = [[ "<<someArray[arrayIdx]<<" ]]" << endl;
            sumTval += someArray[ arrayIdx ];
            cout << ">>> ------- DEBUG: sumTval = [[ " << sumTval << " ]]" << endl;
         }
         else
         {
            cout << ">>> ------- NO-MATCH!!!  [[]]" << endl;
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

