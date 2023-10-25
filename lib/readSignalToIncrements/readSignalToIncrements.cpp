#include "readSignalToIncrements.h"
#include "BitVector.h"
#include "constants.h"

void readSignalToMSIncrements(int buttonPin, BitVector<SIGNALBITVECTORSIZE> & signalBitvector, int incrementLengthInMS, int timeoutIncrements)
{
    int increment = 0;
    int noSignalIncrements = 0;
    while (increment < SIGNALBITVECTORSIZE && noSignalIncrements < timeoutIncrements)
    {
        if (digitalRead(buttonPin) == LOW)
        {
            signalBitvector[increment] = true;
            noSignalIncrements = 0;
        }
        else
        {
            signalBitvector[increment] = false;
            noSignalIncrements++;
        }
        increment++;
        delay(incrementLengthInMS);
    }
}