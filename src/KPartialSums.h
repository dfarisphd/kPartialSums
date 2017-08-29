#ifndef K_PARTIAL_SUMS_FUNC_TEMPLATE_H_
#define K_PARTIAL_SUMS_FUNC_TEMPLATE_H_

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// FILE-NAME: [["KPartialSums.h"]]
//
// PROVIDES:
//
//    template< typename T , size_t N , typename S >
//    size_t
//    kPartialSums (
//       const T (&someArray)[N] ,
//       const S targetSum ,
//       std::vector& retVals
//    )
//
//    size_t
//    decodeBCI (
//       size_t BCIval ,
//       std::vector<size_t>& indexVals
//    )
//
// Objective: This function template calculates the K-Partial-Sums over an
// input array and compares each one to the TargetSum input value.  To return
// the possible matches (which are basically the indices involved in each
// permutation), I use a "Binary Coded Integral" value: the bits of this
// BCI (right-to-left: LSB on the rhs, MSB on the LHS) each match one of the
// array indices to form an unsigned integer, pushed onto the return vector.
//
// As a result of this method of formulating or conceptualizing the problem,
// it becomes much clearer: this is basically an N-Based Counting Problem
// and there are thus (2**N) possible permutations.
//
// The main issue is C/C++ is how to return the result set: Its considered
// bad form to allocate within a function or method - out of scope of the
// calling code (and thus requiring the caller to free/delete or risk memory
// leakage).  To solve this problem, I pass a std::vector by reference as
// as input parameter (an "out" param is #MSFT terminology).
//
// See the code below for more detailed documentation ...
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// SCALABILITY ISSUES:  This methodology for the K-Partial-Sums problem
// and this code for solving it both have VERY VERY SEVERE AND DOWNRIGHT
// CANTANKEROUS SCALABILIY ISSUES:
//
// (1) At 2**N permutations, this problem scales quickly in terms of the
// customary "Big-Oh" O(*) estimates; for example:
//    2**16  =  65,536
//    2**32  =  2,147,483,648
//    2**64  =  9.2 quintillion (9,223,372,036,xxx,xxx,xxx)
//
// (2) This must be factored into the result set/return values ...
// there may naturally be only a fraction of valid result sets,
// still a very very insanely large Big-Oh number.
//
// (3) Unless the input values balance out (in this case positive and
// negative values) but in general some distribution which behaves nice
// over "9 quintillion" operations - - - overflow and underflow is
// utterly assured ;-)
//
// Regardless of the input "Target Sum" whatever that type and value are,
// the operation defined on T and S must scale over the totallity of
// 2**N operations.  Tough task ahead in terms of scalabiity.
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// ALT SCALABILITY:  There is a possibilty that an alternative formulation
// such as GPU Inclusive Scan (or sume such) may solve this problem with much
// better scalability; similar to parallel merge sort.
//
// CONCEPT:  Chunk out the input array, calculate individual k-partial-sums
// and then recombine.  To do this, sorting will be invaluable.  Also, each
// k-partial-sum result (scattered or mapped phase) must now keep track of its
// entire set of partial sum results.  Hueristics will become important to
// simplify the (gather or reduction) phase; just as one example, what is the
// relationship between TargetSum value and partial sum results (is reduction
// operation even feasible for any given set of values or can large numbers
// of partial-sum result from the scatter/map phase be eliminated?
//
// For integers and decimal numbers (and especially for strictly positive
// sets of numbers), this would be almost trivial - and fun:
//    e.g: and partial sum greater than TargetSum eliminated
//    kindof like playing PowerBall ...
//
// GPU or Map-Reduce thus might solve this much larger-scale problem:
// but we are still only talking 2**64 = 9 quintillion permutations!
// For example: It would take 9M GHZ scale processors and 9M GBytes of
// memory just for some fraction of 2**64 scale problems.  But the cloud
// is catching up - especially AWS with GPU instances.  2**64 scale
// could become feasible ...
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// [[ David Faris :: 2017-08-27 ]]
// Copyright (C) 2017 by David W. Faris, PhD
// This original code is placed into the public domain
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

// include(cstdlib) for: size_t
// include(cstdint) for: C99 standard types
#include <cstdlib>
#include <cstdint>

// include(vector) for: std::vector
#include <vector>
using std::vector;

//// include(bitset) for: std::bitset
//#include <bitset>
//using std::bitset;

/// DEFINE: Calculate 2**X - used to calculate sizes and lengths
// best practice: avoid macros like the plague, except in the public domain
#define POW2(x) (1 << (x))

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// template< typename T , size_t N , typename S >
// size_t
// kPartialSums (
//    const T (&someArray)[N] ,
//    const S targetSum ,
//    std::vector& retVals )
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

/// Calculates the K-Partial-Sums over input array, compares each to TargetSum.
/// I use a "Binary Coded Integral" value: the bits of this BCI Index Value
/// (right-to-left: LSB on the rhs, MSB on the LHS) each match one of the
/// array indices to form an unsigned integer, and that is pushed onto the
/// return vector.  To decode BCI Value, simply find all 1-bits and equate
/// that ZERO-Based position to an array index (LSB = ZERO-Index).
///
/// @return: size_t
/// the NUMBER of k-partial-sums matching targetSum value
///
/// @template_param: typename T
/// the TYPE contained within the input array.  input array must define:
/// (1) random access sequence iterator AND (2) operator[] - because in this
/// algorithm, I access elements of the array out of order (in increasing
/// binary count order which will jump around - DO NOT USE THIS ALGO ON GPU!).
/// Memory coalescence on GPU will be very very poor, almost worst case poor.
///
/// type T must define:
///    (1) operator+, to define and calculate the intermediate sum.
///    (2) default constructor that makes sense: T(0) without the zero
///
/// @template_param: typename S
/// the so called target_sum value for k-partial-sums ...
///
/// FINALLY:  sum_over(T) and typename S must share an operator==()
///
/// @return: std::vector<size_t>& retVals
/// initialized reference to vector<size_t> to hold BCI Values
/// BCI Index coding for k-partial-sum matches over the input array
///
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

template< typename T , size_t N , typename S >
uint64_t
kPartialSums
(
   T (&someArray)[N] ,
   S targetSum ,
   std::vector<uint64_t>& retVals
);

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

size_t
decodeBCItoIndexValues
(
   uint64_t BCIval ,
   std::vector<size_t>& indexVals
);

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

#endif // <</END: ifndef header guard (K_PARTIAL_SUMS_FUNC_TEMPLATE_H_)>>

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
// FILE-NAME: [["KPartialSums.h"]]
// [[ David Faris :: 2017-08-27 ]]
// Copyright (C) 2017 by David W. Faris, PhD
// This original code is placed into the public domain
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
