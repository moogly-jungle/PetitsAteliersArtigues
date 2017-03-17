
#include <Arduino.h>
#include "RGB.h"

const int greenLEDPin = 5;    // LED connected to digital pin 5
const int redLEDPin = 6;     // LED connected to digital pin 6
const int blueLEDPin = 7;    // LED connected to digital pin 7

void setupRGB(void)
{
  // set the digital pins as outputs
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

  
void color(int redValue,int greenValue, int blueValue)
{
  /*
  Now that you have a usable value, it's time to PWM the LED.
  */
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}


