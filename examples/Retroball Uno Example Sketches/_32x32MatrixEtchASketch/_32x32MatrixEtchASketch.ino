// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library


#ifdef CORE_TEENSY
const int potA = A6;
const int potB = A3;
const int potC = A4;
const int potD = A7;
RGBmatrixPanel matrix(false, 32);
#else
// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
const int potA = A9;
const int potB = A8;
const int potC = A7;
const int potD = A6;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
#endif

const int buttonSelect = 12;
const int buttonPause = 11;

int myColor = 1;
int redColor = 7;
int greenColor = 0;
int blueColor = 0;

void setup() {
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  matrix.begin();
}

void loop() {
  matrix.drawPixel((analogRead(potD) / 32), (analogRead(potA) / 32), matrix.Color333(redColor, greenColor, blueColor));
  if (digitalRead(buttonSelect) == LOW) {
    matrix.fillScreen(matrix.Color333(0, 0, 0));
  }
  if (digitalRead(buttonPause) == LOW) {
    if (myColor++ > 7) myColor = 1;
    if (bitRead(myColor, 0) == 1) {
      redColor = 7;
    }
    else {
      redColor = 0;
    }
    if (bitRead(myColor, 1) == 1) {
      greenColor = 7;
    }
    else {
      greenColor = 0;
    }
    if (bitRead(myColor, 2) == 1) {
      blueColor = 7;
    }
    else {
      blueColor = 0;
    }
    delay( 100 );
  }
}
