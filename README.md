# kPartialSums

## Algorithms to Compute *ALL* K-Partial Sums of a Set

Objective: Write a “function” that returns the set of
combinations to the K-Partial-Sum Problem: All k-length
combinations of the input "multi-set" (since we allow
repeated elements in the set) which SUM to the given
targetSum value.i

Rather than "combinations" it is more likely: the set
of permutations; combinations typically allow repeats
AABC (for {A,B,C}) of the same element - which if negative
and "zero" elements are allowed for the K-Partial Sum,
the problem becomes indeterminant.

* Addition is Commutative - which states that A + B = B + A
or should be for arbitrary object types that
override operator+ to support something like addition): Thus order does not
matter, as the commutative law states that: A + B = B + A

* Furthermore: Addition is Associative - which states that (A+B)+C=A+(B+C).
Therefore, we can perform the summation of the candidate sequence in any order
as they are all the same (provided again that some arbitrary object types
supporting operator+ implement addition that agrees with  


## SOLUTIONS:  Example 1


```
## EXAMPLE 1:
[2017-08-29 08:20:22.464] [console1] [info] *** INPUT: [[ 5 , 5 , 15 , 10 ]]
[2017-08-29 08:20:22.464] [console1] [info] ***    targetSum: [[ 15 ]]
[2017-08-29 08:20:22.464] [console1] [info] ***    maxNum permutations (!): [[ 16 ]]

these solutions to Example 1 (expressed below) are in BCI: { 4 , 9 , 10 }
are in fact BCI Integers: Binary Coded Indices ...
Express each number in binary (Right/LSB-to-Left/MSB) and the "1/set" bits
will align with the ZERO-Based Indices (also going from Right-to-Left).
One must be very very careful with INDEX RANGE and RHS/LHS.

[2017-08-29 08:20:22.464] [console1] [info] *** [[ K-PARTIAL-SUMS ( kPartialSums() ) ]] ***  CORE ALGORITHM DONE
[2017-08-29 08:20:22.464] [console1] [info] ***    NUMBER OF MATCHES (targetSum matched in InputArray): [[ 3 ]]
[2017-08-29 08:20:22.464] [console1] [info] ***    ALL MATCHES: [[ 4 , 9 , 10 ]]
[2017-08-29 08:20:22.464] [console1] [info] *** [[ K-PARTIAL-SUMS ( kPartialSums() ) ]] ***  CORE ALGORITHM DONE

SOLUTIONS:
[2017-08-29 08:20:22.464] [console] [info] BCI-VAL = [[  4 ]]  -->>  Array Index Values: [[ 2 ]]
[2017-08-29 08:20:22.465] [console] [info] BCI-VAL = [[  9 ]]  -->>  Array Index Values: [[ 0 , 3 ]]
[2017-08-29 08:20:22.465] [console] [info] BCI-VAL = [[ 10 ]]  -->>  Array Index Values: [[ 1 , 3 ]]
```

## SOLUTIONS: Example 2

```
[2017-08-29 08:43:23.370] [console5] [info] ********************************************************************
[2017-08-29 08:43:23.370] [console5] [info] *** [[ K-PARTIAL-SUMS ( kPartialSums( ) ) ]] *** CORE ALGORITHM
[2017-08-29 08:43:23.370] [console5] [info] *** INPUT: [[ 1 , 2 , 3 , 4 ]]
[2017-08-29 08:43:23.370] [console5] [info] ***    targetSum: [[ 6 ]]
[2017-08-29 08:43:23.370] [console5] [info] ***    maxNum permutations (!): [[ 16 ]]
[2017-08-29 08:43:23.370] [console5] [info] ***    NUMBER OF MATCHES (targetSum matched in InputArray): [[ 2 ]]
[2017-08-29 08:43:23.370] [console5] [info] ***    ALL MATCHES: [[ 7 , 10 ]]
[2017-08-29 08:43:23.370] [console5] [info] *** [[ K-PARTIAL-SUMS ( kPartialSums() ) ]] ***  CORE ALGORITHM DONE
[2017-08-29 08:43:23.370] [console5] [info] ********************************************************************
[2017-08-29 08:43:23.370] [console5] [info] ### TIME//SCALABILITY BENCHMARK ONLY:  2e-06 ]]
[2017-08-29 08:43:23.370] [console5] [info] ********************************************************************
[2017-08-29 08:43:23.370] [console6] [info] *** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] ***
[2017-08-29 08:43:23.370] [console6] [info] *** bciVal: [[ 7 ]]
[2017-08-29 08:43:23.370] [console6] [info] *** bitset COUNT   = [[ 3 ]]
[2017-08-29 08:43:23.370] [console6] [info] *** bitset ULLONG  = [[ 7 ]]
[2017-08-29 08:43:23.370] [console6] [info] *** bitset STRING  = [[ 0000000000000000000000000000000000000000000000000000000000000111 ]]
[2017-08-29 08:43:23.370] [console6] [info] ***    TOTAL Number of Bits Found = [[ 3 ]]
[2017-08-29 08:43:23.370] [console6] [info] ***    ARRAY INDICES FOUND = [[ 0 , 1 , 2 ]]
[2017-08-29 08:43:23.370] [console5] [info] ********************************************************************
[2017-08-29 08:43:23.370] [console7] [info] *** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] ***
[2017-08-29 08:43:23.370] [console7] [info] *** bciVal: [[ 10 ]]
[2017-08-29 08:43:23.370] [console7] [info] *** bitset COUNT   = [[ 2 ]]
[2017-08-29 08:43:23.370] [console7] [info] *** bitset ULLONG  = [[ 10 ]]
[2017-08-29 08:43:23.370] [console7] [info] *** bitset STRING  = [[ 0000000000000000000000000000000000000000000000000000000000001010 ]]
[2017-08-29 08:43:23.370] [console7] [info] *** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] *** DONE
[2017-08-29 08:43:23.370] [console7] [info] ***    TOTAL Number of Bits Found = [[ 2 ]]
[2017-08-29 08:43:23.370] [console7] [info] ***    ARRAY INDICES FOUND = [[ 1 , 3 ]]
[2017-08-29 08:43:23.370] [console5] [info] ********************************************************************
```


### Basic Breakfast Serial Algorithm

* The pseudo-code is pretty straightforward as the basic algorithm
is conceptually simple: Hit all permutations, sum them up, and compare.
	- The conceptual and coding work for the Basic Algorithm
	becomes simply book-keeping each permutation.
	- Book-Keeping permutations is very easy: It is basically the
	same as *COUNTING in BINARY* - and so we can COUNT is decimal
	(if we cover the same range [0,2**N] give or take +/-1).
	- Thats a big big big range for large N ...
	- For example: For N = 64 (a very reasonable even smallish array)
	the number of permutations is: 9 QUINTILLION:
	- 9.2 quintillion to be exact ...
	- 9,223,372,036,xxx,xxx,xxx
* I coded the Basic Algorithm in C++11.  Why?
* Templatized: Any Appropriate Type Works for T and S
* Templatized (Part Deux): size_t N (not a formal parameter but a template parameter) for arbitrary size array.
* One downside to Proper C++: We tend not to allocate in methods and functions.
* Thus: Caller must pass std::vector<uint64_t>& to collect solutions.
* Speaking of Solutions: I use Binary Coded Integer Indices (BCI)

```
template< typename T , size_t N , typename S >
uint64_t
kPartialSums (
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
        if( idx & (1 << arrayIdx) ) {
            sumTval += someArray[ arrayIdx ];
        }
     }
     if( sumTval == targetSum )
     {
         retVals.push_back( idx );
         ++retNumVals;
     }
   }
   return( retNumVals );
}
```

### Decode “Binary Coded Integer” into Array Indices

Fairly straightforward: Simply track down the true/1 bits in the BCI value
(with LSB/0-Based Index and MSB/N-1 Based Index).  It requires very very
careful book-keeping and data structures to get it right.  But not difficult.

```
<span style="color: #f2cf4a; font-family: Georgia; font-size: 2em;">
size_t
decodeBCItoIndexValues (
   uint64_t BCIval ,
   std::vector<size_t>& indexVals
)
{

     size_t numBits = 0;
     indexVals.clear();

     // it is VERY EASY to code the bit-shift loop by hand
     // STD::BITSET in C++11 is very convenient though
     //   e.g: any , none , all , first , count , addressable , etc
     // initialize std::bitset with integer value
     std::bitset< 8 * sizeof(BCIval) > bci_val_bitset( BCIval );

     console->info("*** bitset COUNT   = [[ {} ]]", bci_val_bitset.count() );
     console->info("*** bitset ULLONG  = [[ {} ]]", bci_val_bitset.to_ullong() );
     console->info("*** bitset STRING  = [[ {} ]]", bci_val_bitset.to_string() );

   // while there are *ANY* bits set true/1 in the bitset
   // we search for (or define) any to be LEADING/LSB bits
   // then we always shift right ...
   size_t cbit = 0;
   while ( bci_val_bitset.any() ) {
     // while the first bit is not set, shift it away - and track it
     while( !bci_val_bitset.test(0) ) {
       // shift right - hey bus driver, remove that bit
       bci_val_bitset >>= 1;
       ++cbit;
     }
     indexVals.push_back( cbit );
     ++numBits;

     // REMEMBER TO KEEP ON GOING ON - more bits
     bci_val_bitset >>= 1;
     ++cbit;
   }


   // compact way to print vector to stringstream
   console->info("*** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] *** DONE");
   console->info("***    TOTAL Number of Bits Found = [[ {} ]]", numBits );
     std::ostringstream oss;
     for( auto idx : indexVals ) { oss << idx << " , "; }
   console->info("***    ARRAY INDICES FOUND = [[ {} ]]", oss.str() );
   console->info("*** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] *** DONE");
   return( numBits );
}
</span>
```
