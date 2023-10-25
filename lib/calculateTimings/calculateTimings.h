#ifndef CALCULATE_TIMINGS_H
#define CALCULATE_TIMINGS_H

#include "BitVector.h"
#include "constants.h"

/*
- Returns the length in increments of one Morse dot for the signal represented by the bit vector.

- The length of each set of sequental 'on' or 'off' increments is measured as a sample for the entire vector or until the array space runs out.
- The sample array is sorted according to the length of each sample
- 'Off' outliers are 'removed' by being set to 'None' type. An 'off' outlier is defined as being larger than the largest 'on' sample. 'None' type samples are not included in the next step.
- Finally, find the location in the array with the largest difference between neighbouring sample lengths. We consider the smaller length to be the maximum size of a Morse dot.
*/
short calculateTimings(BitVector<SIGNALBITVECTORSIZE> & signalBitvector);

#endif