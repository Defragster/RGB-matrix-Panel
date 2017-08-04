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


int myNumber[4] = {0, 0, 0, 0};
int lastNumber[4] = {0, 0, 0, 0};

void setup() {
  matrix.begin();
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(7, 0, 0));
}

void loop() {
  myNumber[0] = analogRead(potA) / 8;
  myNumber[1] = analogRead(potB) / 8;
  myNumber[2] = analogRead(potC) / 8;
  myNumber[3] = analogRead(potD) / 8;
  // don't bother updating the display UNLESS we have a new number (otherwise we are drawing the same thing over again...)
  for ( int ii = 0; ii < 4; ii++ ) {
    if (myNumber[ii] != lastNumber[ii]) {
      matrix.fillRect(0, ii*8, 31, 8, matrix.Color333(0, 0, 0));
      matrix.setCursor(2 , ii * 8);
      matrix.print(myNumber[ii]);
      //      matrix.setCursor(24, 0);
      for (int index = 0; index < 8; index++) {
        if (bitRead(myNumber[ii], index) == 1) matrix.drawPixel((30 - index), 4 + 8 * ii, matrix.Color333(0, 0, 7));
      }
    }
    lastNumber[ii] = myNumber[ii];
  }
  delay(50);
}

