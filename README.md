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

## Basic Algorithm (No Scalability!)

* C++11 Or Bust
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
