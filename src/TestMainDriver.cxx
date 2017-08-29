//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

// include(vector) for: std::vector
#include <vector>
using std::vector;

// include(bitset) for: std::bitset
#include <bitset>
using std::bitset;

#include <cstdint>
#include <cstddef>

#include <ostream>
using std::ostream;

#include <iostream>
using std::cout;
using std::endl;

#include <cmath>

#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
namespace spd = spdlog;

#include <sstream>
using std::ostringstream;

#include <string>
using std::string;

#include <cstdlib>
#include <ctime>
// clock_t start = clock();
// ( (double)clock() - start ) / CLOCKS_PER_SEC 

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

/// DEFINE: Calculate 2**X - used to calculate sizes and lengths
// best practice: avoid macros like the plague, except in the public domain
#define POW2(x) (1 << (x))

static size_t console_count = 1;

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
//
// template< typename T , size_t N , typename S >
// uint64_t kPartialSums ( --- )
//
// using template<T,size_t> allows us to *NOT* pass the array size
// decided to stick w/c-style arrays based on assignment API & Examples
// this solution solves both issues: use arrays in api + avoid passing size
// PLUS: we now get variable array size (almost by definition)
//
// However, the algorithm must be correct ;-)
//
// NOTE:
// std::vector used for return type to avoid allocating w/in method/function
//
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

template< typename T , size_t N , typename S >
uint64_t
kPartialSums (
   T (&someArray)[N] ,
   S targetSum ,
   std::vector<uint64_t>& retVals
)
{

   uint64_t retNumVals = 0u;
   // uint64_t maxNum = (uint64_t)POW2(N);
   uint64_t maxNum = (uint64_t)( pow(2.0,(double)N) );
   retVals.clear();

   // SPDLOG Configuration within this method
   try {
     int log_console_num = console_count++;
     ostringstream ss;
     ss << "console" << log_console_num;
     string str = ss.str();
     auto console = spd::stdout_color_mt( str );
     console->set_level(spd::level::info);
     console->info("********************************************************************");
     console->info("*** [[ K-PARTIAL-SUMS ( kPartialSums( ) ) ]] *** CORE ALGORITHM");
     console->info("***    targetSum: [[ {} ]]" , targetSum );
     console->info("***    maxNum permutations (!): [[ {} ]]" , maxNum );

     std::ostringstream oss;
     for( auto aaa : someArray ) { oss << aaa << " , "; }
     console->info("*** INPUT: [[ {} ]]" , oss.str() );

   // count from 1 (not the zero permutation {0,0,...0})
   // each count represents a series of bits set to "1"
   // *AND* counting in this way covers *ALL* permutations
   // each set of bits set represents a candidate permutation
   // find those bits and sum the values in the array at those bit positions

   // WHAT HAPPENS IF WE DO SOME TIMING/BENCHMARKS ...
   clock_t start = clock();
   for( uint64_t idx = 1u ; idx < maxNum ; ++idx ) {
     T sumTval = 0;
     for( size_t arrayIdx = 0 ; arrayIdx < N ; ++arrayIdx ) {
        if( idx & (1 << arrayIdx) ) {
            sumTval += someArray[ arrayIdx ];
        }
     }
     console->debug("***    iteration complete: thisKPSum [[ {} ]]" , sumTval );
     if( sumTval == targetSum )
     {
         console->debug("***    its a match made in heaven");
         console->debug("***    ... targetSum  [[ {} ]]" , targetSum );
         console->debug("***    ... thisKPSum  [[ {} ]]" , sumTval );
         console->debug("***    ... idx        [[ {} ]]" , idx );
         retVals.push_back( idx );
         ++retNumVals;
     }
   }
   double unreliable_pseudo_time = ( (double)clock() - start ) / CLOCKS_PER_SEC;

   console->info("*** [[ K-PARTIAL-SUMS ( kPartialSums() ) ]] ***  CORE ALGORITHM DONE");
   console->info("***    NUMBER OF MATCHES (targetSum matched in InputArray): [[ {} ]]" , retNumVals );
     std::ostringstream oohno;
     for( auto aaa : retVals ) { oohno << aaa << " , "; }
   console->info("***    ALL MATCHES: [[ {} ]]" , oohno.str() );
   console->info("*** [[ K-PARTIAL-SUMS ( kPartialSums() ) ]] ***  CORE ALGORITHM DONE");
   console->info("********************************************************************");
   console->info("### TIME//SCALABILITY BENCHMARK ONLY:  {} ]]" , unreliable_pseudo_time);
   console->info("********************************************************************");
   return( retNumVals );

   } catch (const spd::spdlog_ex& ex) {
       std::cout << "*** FATAL( decodeBCItoIndexValues ): SPDLOG Log init failed: "
                 << ex.what() << std::endl;
     return(0);
   }
};

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
decodeBCItoIndexValues ( uint64_t BCIval , std::vector<size_t>& indexVals )
{

   // SPDLOG Configuration within this method
   try {
     int log_console_num = console_count++;
     ostringstream ss;
     ss << "console" << log_console_num;
     string str = ss.str();
     auto console = spd::stdout_color_mt( str );
     console->set_level(spd::level::info);
     console->info("*** [[ K-PARTIAL-SUMS (decodeBCItoIndexValues) ]] ***");
     console->info("*** bciVal: [[ {} ]]",BCIval);
     console->debug("    remember: this is a BINARY CODED INDEX INTEGER");
     console->debug("    (integer value codes for permutation indices in array)");

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
     console->debug("*** bitset PUSHING VALUE   = [[ {} ]]", cbit );
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

   } catch (const spd::spdlog_ex& ex) {
       std::cout << "*** FATAL( decodeBCItoIndexValues ): SPDLOG Log init failed: "
                 << ex.what() << std::endl;
     return(0);
   }
}

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

int
main( int argc , char* argv[] ) {

   // spdlog
   try {

     auto console = spd::stdout_color_mt("console");
     spd::set_level(spd::level::info);
     console->set_level(spd::level::info);
     console->info("*** [[ K-PARTIAL-SUMS (TestMainDriver.cxx) ]] ***");

     uint64_t numMatches  =  0u;
     std::vector<uint64_t> retVals(0);
     uint64_t vec[ 4 ] = { 5ul , 5ul , 15ul , 10ul };
     uint64_t targetSum = (uint64_t)15u;

       // EXAMPLE 1:
       console->debug("*** EXAMPLE 1  :: [[ 5 , 5 , 15 , 10 ]] && targetSum = 15");
       console->debug("*** SOLUTION 1 :: BCI =  4 ... inputs(2)   = targetSum = 15");
       console->debug("*** SOLUTION 2 :: BCI =  9 ... inputs(0,3) = targetSum = 15");
       console->debug("*** SOLUTION 3 :: BCI = 10 ... inputs(1,3) = targetSum = 15");

     // compact way to print vector to stringstream
     std::ostringstream oss; oss << "[[ ";
     for( auto idx : vec ) { oss << idx << " , "; } oss << "]]";
     console->debug("*** EXAMPLE 1  :: [[ 5 , 5 , 15 , 10 ]]: {}" , oss.str() );

     //-------------------------------------------------------------------------
     // CALL K-PARTIAL-SUMS ROUTINE
     console->info( "CALLING \"kPartialSums\" ROUTINE ..." );
     numMatches  =  kPartialSums( vec , targetSum , retVals );
     console->info( "NUM-MATCHES -->> [[ {} ]]" , numMatches );
     //-------------------------------------------------------------------------

     std::ostringstream rvoss;
     for( auto idx : retVals ) { rvoss << idx << " , "; }
     console->info("*** EXAMPLE 1  :: RET-VALS = [[ {} ]]" , rvoss.str() );

     //-------------------------------------------------------------------------
     // PRINT OUT & DEBUG THE BCI-Coded Index Values ...
     console->debug("Printing out BCI Coded Index Values: {} Solutions ...",numMatches);
     if( numMatches ) {
         for( auto bciVal : retVals ) {
           std::vector<size_t> arrayIndexValues(0);
           size_t numIndices = 0;
           numIndices = decodeBCItoIndexValues ( bciVal , arrayIndexValues );
               std::ostringstream aioss;
               for( auto aiv : arrayIndexValues ) { aioss << aiv << " , "; }
               console->info("BCI-VAL = [[ {} ]]  -->>  Array Index Values: [[ {} ]]",bciVal,aioss.str());
         }
     }
//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

     numMatches  =  0u;
     retVals.clear();
     uint64_t vec2[ 4 ] = { 1ul , 2ul , 3ul , 4ul };
     uint64_t targetSum2 = (uint64_t)6u;

     // compact way to print vector to stringstream
     std::ostringstream oss2; oss2 << "[[ ";
     for( auto idx : vec2 ) { oss2 << idx << " , "; } oss2 << "]]";
     console->debug("*** EXAMPLE 2  :: [[ 1 , 2 , 3 , 4 ]]: {}" , oss2.str() );

     //-------------------------------------------------------------------------
     // CALL K-PARTIAL-SUMS ROUTINE
     console->info( "CALLING \"kPartialSums\" ROUTINE ..." );
     numMatches  =  kPartialSums( vec2 , targetSum2 , retVals );
     console->info( "NUM-MATCHES -->> [[ {} ]]" , numMatches );
     //-------------------------------------------------------------------------

     std::ostringstream rvoss2;
     for( auto idx : retVals ) { rvoss2 << idx << " , "; }
     console->info("*** EXAMPLE 2  :: RET-VALS = [[ {} ]]" , rvoss2.str() );

     //-------------------------------------------------------------------------
     // PRINT OUT & DEBUG THE BCI-Coded Index Values ...
     console->debug("Printing out BCI Coded Index Values: {} Solutions ...",numMatches);
     if( numMatches ) {
         for( auto bciVal : retVals ) {
           std::vector<size_t> arrayIndexValues(0);
           size_t numIndices = 0;
           numIndices = decodeBCItoIndexValues ( bciVal , arrayIndexValues );
               std::ostringstream aioss;
               for( auto aiv : arrayIndexValues ) { aioss << aiv << " , "; }
               console->info("BCI-VAL = [[ {} ]]  -->>  Array Index Values: [[ {} ]]",bciVal,aioss.str());
         }
     }

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8

     console->info("*** [[ K-PARTIAL-SUMS (TestMainDriver.cxx) ]] *** DONE");
   } catch (const spd::spdlog_ex& ex) {
       std::cout << "*** FATAL: SPDLOG Log init failed: " << ex.what() << std::endl;
     return(EXIT_FAILURE);
   }
   return( EXIT_SUCCESS );
}

//==+====1====+====2====+====3====+====4====+====5====+====6====+====7====+====8
