This is an Arduino library for our 16x32 and 32x32 RGB LED matrix panels

Pick one up at http://www.adafruit.com/products/420 & http://www.adafruit.com/products/607 !


Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon for Adafruit Industries.  
BSD license, all text above must be included in any redistribution

To download. click the ZIP (download) button, rename the uncompressed folder RGBLEDMatrix. 
Check that the RGBmatrixPanel folder contains RGBmatrixPanel.cpp and RGBmatrixPanel.h

Place the RGBmatrixPanel library folder your arduinosketchfolder/libraries/ folder. 
You may need to create the libraries subfolder if its your first library. 
Restart the IDE.


We also have a great tutorial on Arduino library installation at:
http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use

>> This code worked perfectly on Teensy 3.1, 3.5 and 3.6 when I found this pin map:
 *     Matrix PIN   Teensy 3.5 PIN
 *             R1 - 2
 *             G1 - 3
 *             B1 - 4
 *             R2 - 5
 *             G2 - 6
 *             B2 - 7
 
 I didn't wire up a T_3.2 but it should work just like a T_3.1 or even a T_3.0?
 It did not work on a T_LC.
 
 The other pins are hard wired like this with two commented changes to allow for the 
 hardware at hand to have use of four analog pins for POTS.
#define CLK 19
// #define LAT 18
#define LAT 10
// #define OE  17
#define OE  9
#define A   23
#define B   22
#define C   15
#define D   16

Designed to put Teensy on this PCB: 
https://www.kickstarter.com/projects/1897710270/retroball-build-it-yourself-pixel-fun-for-upto-fou-0/description

With this change to any EXAMPLE I tried it worked to run on my Teensy setup:
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
