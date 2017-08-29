#ifndef K_PARTIAL_SUMS_DEBUG_H_
#define K_PARTIAL_SUMS_DEBUG_H_

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

#include <cstddef>
#include <cstdint>

#include <iostream>
using std::cout;
using std::endl;

/// DEFINE: Calculate 2**X - used to calculate sizes and lengths
// best practice: avoid macros like the plague, except in the public domain
#define POW2(x) (1 << (x))

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

uint64_t
kPartialSums4 ( int *someArray , int targetSum );

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

#endif // <</END: ifndef header guard>>
