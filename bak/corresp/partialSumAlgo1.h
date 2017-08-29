#ifndef PARTIAL_SUMS_ALGO1_H_
#define PARTIAL_SUMS_ALGO1_H_

/// DEFINE: Calculate 2**X - used to calculate sizes and lengths
#define POW2(x) (1 << (x))

#define SIZE4 16
#define SIZE5 32

/// partialSumAlgo1: Computes all permutations and their partial sums, compares to target value.
///    INPUTS:
///    RETURNS:
///    OUTPUTS:
///
/// Algorithm Description:
///
/// This algorithm uses the "Base-N Counting" approach: All permutations are accounted for
/// by counting up from [0,2^N) and treating the permutation place-holder positions as the
/// binary digits. Very simple - although somewhat technical and complex.
///
/// *WARNING: DOES NOT SCALE WELL (past 2^N, where N is 32-64)
/// *There are other scaling issues that would dominate first (roll-over in computing the
/// *partial sums), but variations of this algorithm could be used in Map/Reduce or GPU
/// *implementations: It would resemble Parallel Merge Sort - the input would be chunked
/// *and each chunk would get partial sums and keep track of its chunk-number. The reduce
/// *phase (or reduction phase on the GPU) would have to combine chunked out partial sums.

int
partialSumAlgo1 (
   const int *inputArray ,
   unsigned int inputLength ,
   int targetSum ,
   int * BCIResults );

void convertIntToIndices( unsigned int BCIval , unsigned int maxLength , int *indexArray );

#endif // Header Guard: PARTIAL_SUMS_ALGO1_H_
