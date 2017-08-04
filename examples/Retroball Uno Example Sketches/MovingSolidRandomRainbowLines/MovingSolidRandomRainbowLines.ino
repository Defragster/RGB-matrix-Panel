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
        getRandomColor();
        matrix.drawLine(0, 0, 31, lineX, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){
        getRandomColor();
        matrix.drawLine(lineX, 0, 31, 31, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){
        getRandomColor();
        matrix.drawLine(31, 0, lineX, 31, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){ 
        getRandomColor();
        matrix.drawLine(31, lineX, 0, 31, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){ 
        getRandomColor();
        matrix.drawLine(31, 31, 0, lineX, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){
        getRandomColor();
        matrix.drawLine(lineX, 31, 0, 0, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 0; lineX < 32; lineX++){
        getRandomColor();
        matrix.drawLine(0, 31, lineX, 0, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
    for(lineX = 31; lineX != 0; lineX--){ 
        getRandomColor();
        matrix.drawLine(0, lineX, 31, 0, matrix.Color333(redColor, greenColor, blueColor));
        delay((1023 - analogRead(A5)) / 50);
        //matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
}

void getRandomColor(){
    redColor = 0;
    greenColor = 0;
    blueColor = 0;
    myColor++;
    if(myColor > 7) myColor = 1;
    if(bitRead(myColor, 0) == 1) redColor = 7;
    if(bitRead(myColor, 1) == 1) greenColor = 7;
    if(bitRead(myColor, 2) == 1) blueColor = 7;
}
