#include <iostream>
using std::cerr;
using std::endl;

#include <cstdint>

#include "partialSumAlgo1.h"

int
partialSumAlgo1
(
   const int *inputArray   /**< [in] pointer to input array of arbitrary integers. */ ,
   unsigned int inputLength       /**< [in] length of input array (N = 4 in example). */ ,
   int targetSum                  /**< [in] arbitrary target value to match for all partial sums. */ ,
   int * BCIResults               /**< [out] output array of integers "coding" for matched indices */
)
{

	/// the integer return value (-1 is used for general error condition)
   int retVal = 0;

   /// check null pointer
   if (inputArray == 0) {
	   cerr << "*ERROR: inputArray is NULL" << endl;
	   return(-1);
   }

   /// check inputLength > 0
   if (inputLength <= 0) {
	   cerr << "*ERROR: inputLength must be strictly positive" << endl;
	   return(-1);
   }

   size_t maxNum = (size_t)POW2( inputLength );

   for( size_t idx = 1 ; idx < maxNum ; ++idx ) {
	   int thisSum = 0;
	   for( size_t arrayIndex = 0 ; arrayIndex < inputLength ; ++arrayIndex ) {
		   if( idx & (1 << arrayIndex) )
			   thisSum += inputArray[ arrayIndex ];
	   }
	   if( thisSum == targetSum )
		   BCIResults[ retVal++ ] = idx;
   }

   return( retVal );
}

void
convertIntToIndices (
   unsigned int BCIval ,
   unsigned int maxLength ,
   int *indexArray )
{
	size_t numVals = 0;
	for( size_t idx = 0 ; idx < maxLength ; ++idx )
	{
		if( BCIval & (1 << idx) )
			indexArray[ numVals++ ] = (int)idx;
	}
}
