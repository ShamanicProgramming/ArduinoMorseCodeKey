#include "BitVector.h"
#include "calculateTimings.h"
#include "interpretBitvectorThenWriteToSerial.h"
#include "readSignalToIncrements.h"
#include <Arduino.h>

int button = 7; // Input pin from the button
int greenLed = 12;
int redLed = 13;
int yellowLed = 11;
BitVector<SIGNALBITVECTORSIZE> signalBitvector;

void setup() // Runs once when sketch starts
{
  pinMode(button, INPUT_PULLUP);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Show the user device is ready for input
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);

  // Wait for a signal
  if (digitalRead(button) == LOW)
  {
    // Read mode
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    readSignalToMSIncrements(button, signalBitvector, 50, 40);

    // Go to write mode
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    short dotTiming = calculateTimings(signalBitvector);
    interpretBitvectorThenWriteToSerial(signalBitvector, dotTiming);
  }
}