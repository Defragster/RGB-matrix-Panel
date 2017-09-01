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

int boxXLocation[4] = {0, 12, 20, 25};
int boxYLocation[4] = {5, 12, 8, 25};
int boxColor[4] = {1, 2, 3, 4};
int boxWidth[4] = {4, 4, 3, 5};
int boxHeight[4] = {4, 3, 2, 6};
boolean boxMovingRight[4] = {true, false, true, false};
boolean boxMovingDown[4] = {true, true, false, false};
int boxXDelay[4] = {10, 5, 20, 2};
int boxYDelay[4] = {4, 8, 14, 21};
int boxXDelayDefault[4] = {10, 5, 20, 2};
int boxYDelayDefault[4] = {4, 8, 14, 21};
int screenWidth = 32;
int screenHeight = 32;

void setup() {
  pinMode(buttonSelect, INPUT_PULLUP);
  pinMode(buttonPause, INPUT_PULLUP);
  matrix.begin();
}

void loop() {
  //for(int index = 0; index < 4; index++){
    //matrix.fillRect(boxXLocation[index], boxYLocation[index], (boxXLocation[index] + boxWidth[index] - 1), (boxYLocation[index] + boxHeight[index] - 1), matrix.Color333(0, 7, 0));
  //}
  updateBoxes();  
  matrix.fillRect(4, 2, 8, 12, matrix.Color333(0, 7, 0));
}

void updateBoxes(){
  for(int index = 0; index < 4; index++){
    if(boxXDelay[index] != 0){
      boxXDelay[index]--;
    }
    else{
      boxXDelay[index] = boxXDelayDefault[index];
      if(boxMovingRight[index] == true){
        if((boxXLocation[index] - 1 + boxWidth[index]) < (screenWidth - 1)){
          boxXLocation[index]++;
          if(boxXLocation[index] == (screenWidth - 1)) boxMovingRight[index] = false;
        } 
      }
      else{
        if(boxXLocation[index] > 0){
          boxXLocation[index]--;
          if(boxXLocation[index] == 0) boxMovingRight[index] = true;
        } 
      }
    }   
  } 
}

