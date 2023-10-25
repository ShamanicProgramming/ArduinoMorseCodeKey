#include "calculateTimings.h"
#include "BitVector.h"
#include "constants.h"

enum SampleType {None, On, Off};

// 6 bytes
struct SignalSample
{
    short length = 0;
    SampleType type = None;
};

int compareSamples(const void* pa, const void* pb)
{
    SignalSample a = *(const SignalSample*)pa;
    SignalSample b = *(const SignalSample*)pb;

    if(a.length < b.length) return -1;
    if(a.length > b.length) return 1;
    return 0;
}

short calculateTimings(BitVector<SIGNALBITVECTORSIZE> & signalBitvector)
{

    SignalSample signalSamples[SIGNALSAMPLEARRAYSIZE]; // 384 bytes
    short signalSampleIndex = 0;
    short currentLength = 0;
    SampleType currentType;
    if(signalBitvector[0])
    {
        currentType = On;
    }
    else
    {
        currentType = Off;
    }

    // Get all the samples
    for(short i = 0; i < SIGNALBITVECTORSIZE; i++)
    {
        bool value = signalBitvector[i];
        if(value == true && currentType == Off)
        {
            signalSamples[signalSampleIndex].length = currentLength;
            signalSamples[signalSampleIndex].type = currentType;
            currentType = On;
            currentLength = 0;
            signalSampleIndex++;
        }
        else if (value == false && currentType == On)
        {
            signalSamples[signalSampleIndex].length = currentLength;
            signalSamples[signalSampleIndex].type = currentType;
            currentType = Off;
            currentLength = 0;
            signalSampleIndex++;
        }
            currentLength += 1;

        // break if we run over the sample limit
        if(signalSampleIndex > SIGNALSAMPLEARRAYSIZE)
        {
            break;
        }
    }

    // Sort samples

    // Sort
    qsort(signalSamples, SIGNALSAMPLEARRAYSIZE, sizeof(SignalSample), compareSamples);

    // Set outliers to None type
    // Find the largest on signal
    short largestOn = 0;
    for(SignalSample sample : signalSamples)
    {
        if(sample.type == On && sample.length > largestOn)
        {
            largestOn = sample.length;
        }
    }
    // Set anything with a larger length to None type
    for(SignalSample sample : signalSamples)
    {
        if (sample.type == Off && sample.length > largestOn)
        {
            sample.type = None;
        }
    }

    // Find dot timing

    short largestDifference = 0;
    short standardDotTiming = 0;
    for(short i = 0; i < SIGNALSAMPLEARRAYSIZE - 1; i++)
    {
        if(signalSamples[i].type != None && signalSamples[i+1].type != None)
        {
            short timingDifference = signalSamples[i+1].length - signalSamples[i].length;
            if(largestDifference < timingDifference)
            {
                largestDifference = timingDifference;
                standardDotTiming = signalSamples[i].length;
            }
        }
    }

    return standardDotTiming;
}