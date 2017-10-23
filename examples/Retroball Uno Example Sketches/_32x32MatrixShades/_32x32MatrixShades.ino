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

static uint8_t rr = 0, gg = 0, bb = 0;
static uint8_t NOwait = 0;
void setup() {
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  matrix.begin();


}

void loop() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  if ( 0 == rr && 0 == bb && 0 == gg ) {
    brightTest();
    //    delay ( 500 * (1+NOwait) );
    delay((1023 - analogRead(potA)) / 2);
    while (!NOwait && digitalRead(buttonSelect) == HIGH ) 
    if ( !digitalRead(buttonPause)) {
      if ( NOwait ) NOwait=0;
      else NOwait =1;
      delay(200);
    }
    if ( !digitalRead(buttonPause)) {
      if ( NOwait ) NOwait=0;
      else NOwait =1;
      delay(200);
    }
    //matrix.fillScreen(matrix.Color333(0, 0, 0));
  }
  for ( uint8_t yy = 0; yy < 32; yy++ ) {
    for ( uint8_t xx = 0; xx < 32; xx += 2 ) {
      matrix.drawPixel( xx, yy, matrix.Color333( rr, gg, bb ) );
      matrix.drawPixel( xx + 1, yy, matrix.Color333( rr, gg, bb ) );
      rr++;
      if ( rr > 7 ) {
        gg++;
        rr = 0;
      }
      if ( gg > 7 ) {
        bb++;
        gg = 0;
        yy++;
      }
      if ( bb > 7 ) {
        bb = 0; rr = 0; gg = 0;
        xx = yy = 40;
      }
    }
  }
  //    delay ( 500 * (1+NOwait) );
  delay((1023 - analogRead(potA)) / 2);
  while (!NOwait && digitalRead(buttonSelect) == HIGH )
    if ( !digitalRead(buttonPause)) {
      if ( NOwait ) NOwait=0;
      else NOwait =1;
      delay(200);
    }
}

void brightTest() {
  for ( uint8_t yy = 0; yy < 32; yy++ ) {
    for ( uint8_t xx = 0; xx < 32; xx += 4 ) {
      matrix.drawLine( xx, yy, xx + 2, yy, matrix.Color333( rr, gg, bb ) );
      rr++;
    }
  }
  rr = 0;
  delay((1023 - analogRead(potA)) / 2);
  while (!NOwait && digitalRead(buttonSelect) == HIGH ) ;
  for ( uint8_t yy = 0; yy < 32; yy++ ) {
    for ( uint8_t xx = 0; xx < 32; xx += 4 ) {
      matrix.drawLine( xx, yy, xx + 2, yy, matrix.Color333( rr, gg, bb ) );
      gg++;
    }
  }
  gg = 0;
  delay((1023 - analogRead(potA)) / 2);
  while (!NOwait && digitalRead(buttonSelect) == HIGH ) ;
  for ( uint8_t yy = 0; yy < 32; yy++ ) {
    for ( uint8_t xx = 0; xx < 32; xx += 4 ) {
      matrix.drawLine( xx, yy, xx + 2, yy, matrix.Color333( rr, gg, bb ) );
      bb++;
    }
  }
  bb = 0;
}