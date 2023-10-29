#ifndef READ_SIGNAL_TO_INCREMENTS_H
#define READ_SIGNAL_TO_INCREMENTS_H

#include "BitVector.h"
#include "constants.h"

/*
- Continously reads from the pin and records a digital signal value in the provided signal Bitvector at evey increment length
- Reading ends once either reaching the end of the bitvector or there is no signal for the duration of the timeout parameter.
- We assume that the buttonPin is configured to INPUT_PULLUP

- Increase the possible length of a message by increasing the SIGNALBITVECTORSIZE.
- Increase the resolution of the data (for fast Morse code users) by reducing incrementLengthInMS. This will reduce the message length unless SIGNALBITVECTORSIZE is increased.
*/
void readSignalToMSIncrements(int buttonPin, BitVector<SIGNALBITVECTORSIZE> &signalBitvector, int incrementLengthInMS, int timeoutMiliseconds);

#endif