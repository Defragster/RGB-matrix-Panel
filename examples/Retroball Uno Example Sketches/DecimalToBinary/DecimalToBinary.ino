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

int myNumber[4] = {0, 0, 0, 0};
int lastNumber[4] = {128, 128, 128, 128};
uint8_t bCl = 7;
uint8_t bCr = 7;

void setup() {
  Serial.begin( 19200);
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  matrix.begin();
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setTextColor(matrix.Color333(7, 0, 0));

  int tt = micros();
  int cc = 0;
  //for ( int jj=0; jj<23; jj++ )
  while ( 1000000 > (micros() - tt) ) {
    for ( int ii = 7; ii > 0; ii-- ) {
      matrix.fillScreen(matrix.Color333(ii, ii, ii));
      //delay(1500);
      cc++;
    }
    delay(45);
    matrix.fillScreen(matrix.Color333(7, 0, 0));
    delay(45);
    matrix.fillScreen(matrix.Color333(0, 7, 0));
    delay(45);
    matrix.fillScreen(matrix.Color333(0, 0, 7));
    delay(45);
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    delay(45);
  }
  Serial.println( micros() - tt );
  Serial.println( cc );
  Serial.println( F_CPU );
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}


void loop() {
  uint8_t bDelt = 0;
  if (digitalRead(buttonSelect) == LOW) {
    if ( bCl == 0  )
      bCl = 7;
    else bCl = 0;
    delay(80);
    bDelt = 4;
  }
  if (digitalRead(buttonPause) == LOW) {
    if ( bCr == 0 )
      bCr = 7;
    else bCr = 0;
    delay(80);
    bDelt = 4;
  }
  myNumber[0] = analogRead(potA);
  myNumber[1] = analogRead(potB);
  myNumber[2] = analogRead(potC);
  myNumber[3] = analogRead(potD);
  // don't bother updating the display UNLESS we have a new number (otherwise we are drawing the same thing over again...)
  for ( int ii = 0; ii < 4; ii++ ) {
    for (int index = 0; index < 8; index++) {
      if (bitRead(myNumber[ii] / 8, index) == 1) matrix.drawPixel((30 - index), 2 + 8 * ii, matrix.Color333(0, 7 - bCr, bCr));
      if (bitRead(myNumber[ii] / 8, index) == 1) matrix.drawPixel((30 - index), 3 + 8 * ii, matrix.Color333(bCl, 7, bCr));
      if (bitRead(myNumber[ii] / 8, index) == 1) matrix.drawPixel((30 - index), 4 + 8 * ii, matrix.Color333(bCl, 7 - bCl, 0));
    }
    if (bDelt || myNumber[ii] != lastNumber[ii]) {
      int difl = myNumber[ii] - lastNumber[ii];
      if (bDelt || difl > 7 || difl < -7)       {
        uint8_t chf = 0;
        if (myNumber[ii] / 8 < 100) chf++;
        if (myNumber[ii] / 8 < 10) chf++;
        matrix.fillRect(0, ii * 8, 31, 8, matrix.Color333(0, 0, 0));
        matrix.setCursor(2 + chf * 6 , ii * 8);
        matrix.print(myNumber[ii] / 8);
        if ( bDelt ) bDelt--;
        lastNumber[ii] = myNumber[ii];
      }
    }
  }
  delay(50);
}

