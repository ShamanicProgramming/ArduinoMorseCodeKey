#include "interpretBitvectorAsKeystrokes.h"
#include "constants.h"
#include "BitVector.h"
#include "Keyboard.h"

// set the correct key value of the keyboard buffer
char calculateCharToSend(short morseSignals)
{
  switch (morseSignals)
  {
  case 0:
    return ' ';
  case 12:
    return 'a';
  case 2111:
    return 'b';
  case 2121:
    return 'c';
  case 211:
    return 'd';
  case 1:
    return 'e';
  case 1121:
    return 'f';
  case 221:
    return 'g';
  case 1111:
    return 'h';
  case 11:
    return 'i';
  case 1222:
    return 'j';
  case 212:
    return 'k';
  case 1211:
    return 'l';
  case 22:
    return 'm';
  case 21:
    return 'n';
  case 222:
    return 'o';
  case 1221:
    return 'p';
  case 2212:
    return 'q';
  case 121:
    return 'r';
  case 111:
    return 's';
  case 2:
    return 't';
  case 112:
    return 'u';
  case 1112:
    return 'v';
  case 122:
    return 'w';
  case 2112:
    return 'x';
  case 2122:
    return 'y';
  case 2211:
    return 'z';
  case 12222:
    return '1';
  case 11222:
    return '2';
  case 11122:
    return '3';
  case 11112:
    return '4';
  case 11111:
    return '5';
  case 21111:
    return '6';
  case 22111:
    return '7';
  case 22211:
    return '8';
  case 22221:
    return '9';
  case 22222:
    return '0';
  }
  return '?';
}

/*
- Write the character via USB, imitating a keyboard. The character to send is passed in via a short where '.' is 1 and '-' is 2.
- E.g. 1122 would be interpreted as "..--".
*/
void writeViaUSB(short characterToSend)
{
  char character = calculateCharToSend(characterToSend);
  Keyboard.write(character);
}

void interpretBitvectorAsKeystrokes(BitVector<SIGNALBITVECTORSIZE> &signalBitvector, short dotTiming)
{
  short currentCharacter = 0;
  short sectionLength = 1;
  bool currentSection = signalBitvector[0];
  short wordSeperatorLength = dotTiming * 7;
  short charSeperatorLength = dotTiming * 3;

  for (short i = 1; i < SIGNALBITVECTORSIZE; i++)
  {
    if (signalBitvector[i] != currentSection) // We just switched to a new section
    {
      if (currentSection) // Previous section was 'on'
      {
        currentCharacter = currentCharacter * 10;
        if (sectionLength > dotTiming)
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
        if (sectionLength >= charSeperatorLength && sectionLength < wordSeperatorLength)
        {
          delay(50);
          writeViaUSB(currentCharacter);
          currentCharacter = 0;
        }
        // Detecting word seperator. Send last character then a space.
        if (sectionLength >= wordSeperatorLength)
        {
          delay(50);
          writeViaUSB(currentCharacter);
          delay(50);
          writeViaUSB(0);
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
  if (currentCharacter != 0)
  {
    writeViaUSB(currentCharacter);
  }
}