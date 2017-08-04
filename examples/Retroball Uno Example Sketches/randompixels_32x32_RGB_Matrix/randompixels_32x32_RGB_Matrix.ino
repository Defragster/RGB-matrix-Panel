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

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

uint8_t redLED = 0;
uint8_t greenLED = 0;
uint8_t blueLED = 0;

void setup() {
  matrix.begin();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void loop() {
  if(random(0,2) == 0) redLED = 0;
  else redLED = 7;
  if(random(0,2) == 0) greenLED = 0;
  else greenLED = 7;
  if(random(0,2) == 0) blueLED = 0;
  else blueLED = 7;
  matrix.drawPixel(random(0,32), random(0,32), matrix.Color333(redLED, greenLED, blueLED)); 
  delay(1);
}
