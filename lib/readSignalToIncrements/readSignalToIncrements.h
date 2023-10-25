#ifndef READ_SIGNAL_TO_INCREMENTS_H
#define READ_SIGNAL_TO_INCREMENTS_H

#include "BitVector.h"
#include "constants.h"

/*
- Continously reads from the pin and records a digital signal value in the provided signal Bitvector at evey increment length
- Reading ends once either reaching the end of the bitvector or there is no signal for the number of increments set by the timeout.
- We assume that the buttonPin is configured to INPUT_PULLUP
*/
void readSignalToMSIncrements(int buttonPin, BitVector<SIGNALBITVECTORSIZE> & signalBitvector, int incrementLengthInMS, int timeoutIncrements);

#endif