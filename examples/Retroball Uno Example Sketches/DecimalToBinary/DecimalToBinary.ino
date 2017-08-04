// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
// If your matrix has the DOUBLE HEADER input, use:
//#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
//#define LAT 9
//#define OE  10
//#define A   A3
//#define B   A2
//#define C   A1
//#define D   A0
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int myNumber = 0;
int lastNumber = 0;

void setup() {
  matrix.begin();
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(7,0,0));
}

void loop() {
  myNumber = analogRead(A5) / 8;
  // don't bother updating the display UNLESS we have a new number (otherwise we are drawing the same thing over again...)
  if(myNumber != lastNumber){
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.setCursor(10, 5);
    matrix.print(myNumber);
    for(int index = 0; index < 8; index++){
      if(bitRead(myNumber, index) == 1) matrix.drawPixel((20 - index), 16, matrix.Color333(0, 0, 7));
    }
    delay(50);
  }
  lastNumber = myNumber;
}

