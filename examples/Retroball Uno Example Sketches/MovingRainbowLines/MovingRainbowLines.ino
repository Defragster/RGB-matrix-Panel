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
const int potA = A5;
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
#endif

const int buttonSelect = 12;
const int buttonPause = 11;
int myColor = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int lineX = 0;
int lineY = 0;
int myDelay = 5;

void setup() {
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  matrix.begin();
}

void loop() {
    for(lineX = 0; lineX < 32; lineX++){  
        matrix.drawLine(0, 0, 31, lineX, matrix.Color333(7, 0, 0));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){  
        matrix.drawLine(lineX, 0, 31, 31, matrix.Color333(0, 7, 0));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){  
        matrix.drawLine(31, 0, lineX, 31, matrix.Color333(0, 0, 7));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){  
        matrix.drawLine(31, lineX, 0, 31, matrix.Color333(7, 7, 0));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){  
        matrix.drawLine(31, 31, 0, lineX, matrix.Color333(7, 0, 7));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){  
        matrix.drawLine(lineX, 31, 0, 0, matrix.Color333(0, 7, 7));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){  
        matrix.drawLine(0, 31, lineX, 0, matrix.Color333(7, 7, 7));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){  
        matrix.drawLine(0, lineX, 31, 0, matrix.Color333(0, 0, 7));
        delay((1023 - analogRead(potA)) / 50);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
}
