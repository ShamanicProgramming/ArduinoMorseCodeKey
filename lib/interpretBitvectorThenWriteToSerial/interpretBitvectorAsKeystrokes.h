#ifndef INTERPRET_BITVECTOR_THEN_WRITE_TO_SERIAL_H
#define INTERPRET_BITVECTOR_THEN_WRITE_TO_SERIAL_H

#include "constants.h"
#include "BitVector.h"

/*
- Interprets Morse characters in the bitvector one at a time, sending each through usb as a keystroke.
*/
void interpretBitvectorAsKeystrokes(BitVector<SIGNALBITVECTORSIZE> &signalBitvector, short dotTiming);

#endif