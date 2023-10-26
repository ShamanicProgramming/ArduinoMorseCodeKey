#ifndef CALCULATE_TIMINGS_H
#define CALCULATE_TIMINGS_H

#include "BitVector.h"
#include "constants.h"

/*
- Returns the length in increments of one Morse dot for the signal represented by the bit vector.

- The length of each series of sequental 'on' increments is measured as a sample for the entire vector or until the array space runs out.
- The sample array is sorted according to the length of each sample
- Finally, we find the location in the array with the largest difference between neighbouring sample lengths. We consider the smaller length to be the maximum size of a Morse dot.
*/
short calculateTimings(BitVector<SIGNALBITVECTORSIZE> &signalBitvector);

#endif