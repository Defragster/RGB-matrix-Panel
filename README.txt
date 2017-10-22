Update 10/21/17:

*** WARNING - don't use this on a T_3.6 ***
It seems the POTS are wired to VIN 5V - not from the cut Jumper to 3.3V.
*** WARNING - don't use this on a T_3.6 ***


Update 10/20/2017: Built a T_3.xx into my RetroBall and it works.
Quick update for now - the below should be helpful - for now latest notes in this forum post:
https://forum.pjrc.com/threads/45772-32x32-RGB-LED-Matrix-with-a-Teensy-footprint?p=157109&viewfull=1#post157109

Updating this for RetroBall on Teensy usage Tools I use on Windows:
TyCommander is a simple way to upload HEX files - I'll put some precompiled T_3.5 Hex files in Examples.
Pull down this ZIP end extract to a folder then unblock the "TyCommander.exe" and run it:
https://bintray.com/koromix/tytools/tytools/view#files/ <click FILES then the UPDATED column>
I'm using this copy current today: https://bintray.com/koromix/tytools/download_file?file_path=TyTools-0.8.8-win64.zip

For Full Arduino Install go here and 'Download the Arduino IDE' - I pull down the ZIP and extract to a folder on a drive root:
https://www.arduino.cc/en/Main/Software [ current version today is 1.8.4 ]

For Teensy to use the latest IDE build the current 'Beta' 1.39b1 is required: https://forum.pjrc.com/threads/46089-Teensyduino-1-39-Beta-1
Start the installer and point it to where the IDE was unzipped. It modifies it in place adding the needed support for Teensy.

To build the LIBRARY has to be in 'your' sketchbook\libraries folder.
On my system this is: I:\tCode\libraries\RGB-matrix-Panel
I unzip the IDE to I:\arduino-1.8.4, the default sketchbook location is within that folder as I:\arduino-1.8.4\libraries
Using that gets confusing as the IDE version changes so I made folder "I:\tCode" where I store all my sketches.
In the IDE I use : "File / Preferences / Sketchbook Location " to growse and set "I:\tCode" for that
Then in that folder I create: "I:\tCode\libraries" 

Wherever you keep your "sketchbook_folder\libraries\RGB-matrix-Panel" - is where these Github files need to be placed to build.

For Teensy there is a great FORUM - https://forum.pjrc.com and the https://www.pjrc.com/teensy/td_download.html for product details. That last link shows installing TeensyDuino in detail and notes the shipped Blinking Teensy needs a press of the [PROGRAM] button to initiate after the first 'Verify' build.


-----------
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
