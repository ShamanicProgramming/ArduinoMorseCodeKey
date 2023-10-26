#include "interpretBitvectorThenWriteToSerial.h"
#include "constants.h"
#include "BitVector.h"

uint8_t outputBuf[8] = {0};

// set the correct key value of the keyboard buffer
void calculateBufToSend(short morseSignals, uint8_t outputBuf[8])
{
  switch(morseSignals)
  {
    case 0:
      outputBuf[2] = 44; // Spacebar
      break;
    case 12:
      outputBuf[2] = 4; // A
      break;
    case 2111:
      outputBuf[2] = 5; // B
      break;
    case 2121:
      outputBuf[2] = 6; // C
      break;
    case 211:
      outputBuf[2] = 7; // D
      break;
    case 1:
      outputBuf[2] = 8; // E
      break;
    case 1121:
      outputBuf[2] = 9; // F
      break;
    case 221:
      outputBuf[2] = 10; // G
      break;
    case 1111:
      outputBuf[2] = 11; // H
      break;
    case 11:
      outputBuf[2] = 12; // I
      break;
    case 1222:
      outputBuf[2] = 13; // J
      break;
    case 212:
      outputBuf[2] = 14; // K
      break;
    case 1211:
      outputBuf[2] = 15; // L
      break;
    case 22:
      outputBuf[2] = 16; // M
      break;
    case 21:
      outputBuf[2] = 17; // N
      break;
    case 222:
      outputBuf[2] = 18; // O
      break;
    case 1221:
      outputBuf[2] = 19; // P
      break;
    case 2212:
      outputBuf[2] = 20; // Q
      break;
    case 121:
      outputBuf[2] = 21; // R
      break;
    case 111:
      outputBuf[2] = 22; // S
      break;
    case 2:
      outputBuf[2] = 23; // T
      break;
    case 112:
      outputBuf[2] = 24; // U
      break;
    case 1112:
      outputBuf[2] = 25; // V
      break;
    case 122:
      outputBuf[2] = 26; // W
      break;
    case 2112:
      outputBuf[2] = 27; // X
      break;
    case 2122:
      outputBuf[2] = 28; // Y
      break;
    case 2211:
      outputBuf[2] = 29; // Z
      break;
    case 12222:
      outputBuf[2] = 30; // 1 char
      break;
    case 11222:
      outputBuf[2] = 31; // 2 char
      break;
    case 11122:
      outputBuf[2] = 32; // 3 char
      break;
    case 11112:
      outputBuf[2] = 33; // 4 char
      break;
    case 11111:
      outputBuf[2] = 34; // 5 char
      break;
    case 21111:
      outputBuf[2] = 35; // 6 char
      break;
    case 22111:
      outputBuf[2] = 36; // 7 char
      break;
    case 22211:
      outputBuf[2] = 37; // 8 char
      break;
    case 22221:
      outputBuf[2] = 38; // 9 char
      break;
    case 22222:
      outputBuf[2] = 39; // 0 char
      break;
  }
}

/*
- Write the character to serial to be send via USB, imitating a keyboard. The character to send is passed in via a short where '.' is 1 and '-' is 2.
- E.g. 1122 would be interpreted as "..--".
*/
void writeToSerial(short characterToSend)
{
    calculateBufToSend(characterToSend, outputBuf);
    Serial.write(outputBuf, 8);
    // Release key
    outputBuf[2] = 0;
    Serial.write(outputBuf, 8);
}

void interpretBitvectorThenWriteToSerial(BitVector<SIGNALBITVECTORSIZE> & signalBitvector, short dotTiming)
{
    short currentCharacter = 0;
    short sectionLength = 1;
    bool currentSection = signalBitvector[0];
    short wordSeperatorLength = dotTiming * 7;
    short charSeperatorLength = dotTiming * 3;

    for(short i = 1; i < SIGNALBITVECTORSIZE; i++)
    {
        if(signalBitvector[i] != currentSection) // We just switched to a new section
        {
            if(currentSection) // Previous section was 'on'
            {
                currentCharacter = currentCharacter * 10;
                if(sectionLength > dotTiming)
                {
                    currentCharacter += 2;
                }
                else
                {
                    currentCharacter += 1;
                }
            }
            else // Previous section was 'off'
            {
                // Detecting character seperator
                if(sectionLength >= charSeperatorLength && sectionLength < wordSeperatorLength)
                {
                    delay(50);
                    writeToSerial(currentCharacter);
                    currentCharacter = 0;
                }
                // Detecting word seperator. Send last character then a space.
                if(sectionLength >= wordSeperatorLength)
                {
                    delay(50);
                    writeToSerial(currentCharacter);
                    delay(50);
                    writeToSerial(0);
                    currentCharacter = 0;
                }
            }

            // reset to start counting the new section
            currentSection = signalBitvector[i];
            sectionLength = 1;
        }
        else
        {
            sectionLength++;
        }
    }
    // Send any remaining characters
    if(currentCharacter != 0)
    {
      writeToSerial(currentCharacter);
    }

}