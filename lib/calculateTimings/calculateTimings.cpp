#include "calculateTimings.h"
#include "BitVector.h"
#include "constants.h"

int compareSamples(const void *pa, const void *pb)
{
    short a = *(const short *)pa;
    short b = *(const short *)pb;

    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

short calculateTimings(BitVector<SIGNALBITVECTORSIZE> &signalBitvector)
{

    short signalSamples[SIGNALSAMPLEARRAYSIZE] = {0};
    short signalSampleIndex = 0;
    short currentLength = 0;

    // Get all the samples
    for (short i = 0; i < SIGNALBITVECTORSIZE; i++)
    {
        bool value = signalBitvector[i];
        if (value == true)
        {
            currentLength++;
        }
        else if (value == false && currentLength != 0) // currentLength != 0 ensures we don't add empty entries for every '0' bit
        {
            signalSamples[signalSampleIndex] = currentLength;
            signalSampleIndex++;
            currentLength = 0;
        }

        // break if we run over the sample limit
        if (signalSampleIndex > SIGNALSAMPLEARRAYSIZE)
        {
            break;
        }
    }

    // Sort samples
    qsort(signalSamples, SIGNALSAMPLEARRAYSIZE, sizeof(signalSamples[0]), compareSamples);

    // Find dot timing
    short largestDifference = 0;
    short standardDotTiming = 0;
    for (short i = 0; i < SIGNALSAMPLEARRAYSIZE - 1; i++)
    {
        short timingDifference = signalSamples[i + 1] - signalSamples[i];
        if (largestDifference < timingDifference)
        {
            largestDifference = timingDifference;
            standardDotTiming = signalSamples[i];
        }
    }

    return standardDotTiming;
}