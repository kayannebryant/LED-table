//carriage return is ascii code of 13
//x is enter.. required to submit current command
//a is choose
//left is l, right is r, up is u, down is d
//Serial.print("hello");
//start of fast led declarations/imports
#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    10
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int incomingByte = 0;   // for incoming serial data
int currentLed=0;



//start of neomatrix declarations/imports

// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif
#define PIN 5
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(10, 10, LED_PIN,
        NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
        NEO_RGB            + NEO_KHZ800);

//never used?
const uint16_t colors[] = {
        matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        FastLED.addLeds<LED_TYPE, LED_PIN> (leds, NUM_LEDS);
        matrix.begin();
        matrix.setTextWrap(false);
        matrix.setBrightness(40);
        matrix.setTextColor(colors[0]);
}

//not sure what this is necessary for
int x    = matrix.width();
int pass = 0;

void loop() {
//GRB for order of Color( , , )
 matrix.fillScreen(matrix.Color(0,255,0));
  //not sure what set Cursor does 
  matrix.setCursor(x, 0);
  //the start of the pixels needs to be arranged once connected to grid (0,0) is 10 from the end (first position of last row because we have it set to start at top right
  matrix.drawPixel(0,1,matrix.Color(0,0,255));
  matrix.show();

//when combining the fast led method below to set individual leds, it doesnt align right because of new matrix set up so put above code using matrix.drawPixel into conditional statements below (the if letter u etc is pressed)
//leds[currentLed] = CRGB::LimeGreen
       char serinput;
        if (Serial.available() ) {
           serinput = Serial.read();
        }
        /*
         * todo: add right and left controls, add tic tac toe
         */
        /*
         * moves up and turns place white when over the spot
         * todo: not overwrite the spots colored already
         */
        if ((char)serinput == 'u' ){ 
          currentLed+=1;
          leds[currentLed] = CRGB::LimeGreen; FastLED.show(); //delay(3000);
        }
        /*
         * moves down and turns place white when over the spot
         * todo: not overwrite the spots colored already, turn off when not hovering over anymore
         */
        if ((char)serinput == 'd' ){ 
          currentLed-=1;
          //if(){
            leds[currentLed] = CRGB::LimeGreen; FastLED.show(); //delay(3000);
          //}
        }
        /*
         * selects the spot by changing color to white, turn off when not hovering over anymore
         */
        if ((char)serinput == 'a' ){ 
          leds[currentLed] = CRGB::White; FastLED.show(); //delay(3000);
        }
        
    
        
       
        
}
