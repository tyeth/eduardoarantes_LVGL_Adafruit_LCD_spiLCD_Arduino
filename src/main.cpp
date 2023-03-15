/**
  ESP32s3 adaptation by Tyeth Gundry
  Work in progress LVGL simple test.

  https://wokwi.com/projects/359264266487565313
 */

/***************************************************
  This uses code written by Limor Fried/Ladyada for Adafruit Industries.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
 ****************************************************/


//#include <Adafruit_GFX.h>    // Core graphics library
// #include <SPI.h>       // this is needed for display
// #include <Adafruit_ILI9341.h>
// #include <Arduino.h>      // this is needed for FT6206
// #include <Adafruit_FT6206.h>

// // The FT6206 uses hardware I2C (SCL/SDA)
// Adafruit_FT6206 ctp = Adafruit_FT6206();

// // // The display also uses hardware SPI, plus #9 & #10
// // #define TFT_CS 10
// // #define TFT_DC 9
// #define TFT_DC 2
// #define TFT_CS 15
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// // Size of the color selection boxes and the paintbrush size
// #define BOXSIZE 40
// #define PENRADIUS 3
// int oldcolor, currentcolor;

// void setup(void) {
//   //while (!Serial);     // used for leonardo debugging

//   Serial.begin(115200);
//   Serial.println(F("Cap Touch Paint!"));
  
//   Wire.setPins(10, 8); // redefine first I2C port to be on pins 10/8
//   tft.begin();

//   if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
//     Serial.println("Couldn't start FT6206 touchscreen controller");
//     while (1);
//   }

//   Serial.println("Capacitive touchscreen started");
  
//   tft.fillScreen(ILI9341_BLACK);
  
//   // make the color selection boxes
//   tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
//   tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
//   tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
//   tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
//   tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
//   tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
 
//   // select the current color 'red'
//   tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//   currentcolor = ILI9341_RED;
// }

// void loop() {
//   delay(10);
//   // Wait for a touch
//   if (! ctp.touched()) {
//     return;
//   }

//   // Retrieve a point  
//   TS_Point p = ctp.getPoint();
  
//  /*
//   // Print out raw data from screen touch controller
//   Serial.print("X = "); Serial.print(p.x);
//   Serial.print("\tY = "); Serial.print(p.y);
//   Serial.print(" -> ");
//  */

//   // flip it around to match the screen.
//   p.x = map(p.x, 0, 240, 240, 0);
//   p.y = map(p.y, 0, 320, 320, 0);

//   // Print out the remapped (rotated) coordinates
//   Serial.print("("); Serial.print(p.x);
//   Serial.print(", "); Serial.print(p.y);
//   Serial.println(")");
  

//   if (p.y < BOXSIZE) {
//      oldcolor = currentcolor;

//      if (p.x < BOXSIZE) { 
//        currentcolor = ILI9341_RED; 
//        tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      } else if (p.x < BOXSIZE*2) {
//        currentcolor = ILI9341_YELLOW;
//        tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      } else if (p.x < BOXSIZE*3) {
//        currentcolor = ILI9341_GREEN;
//        tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      } else if (p.x < BOXSIZE*4) {
//        currentcolor = ILI9341_CYAN;
//        tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      } else if (p.x < BOXSIZE*5) {
//        currentcolor = ILI9341_BLUE;
//        tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      } else if (p.x <= BOXSIZE*6) {
//        currentcolor = ILI9341_MAGENTA;
//        tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
//      }

//      if (oldcolor != currentcolor) {
//         if (oldcolor == ILI9341_RED) 
//           tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
//         if (oldcolor == ILI9341_YELLOW) 
//           tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
//         if (oldcolor == ILI9341_GREEN) 
//           tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
//         if (oldcolor == ILI9341_CYAN) 
//           tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
//         if (oldcolor == ILI9341_BLUE) 
//           tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
//         if (oldcolor == ILI9341_MAGENTA) 
//           tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
//      }
//   }
//   if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
//     tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
//   }
// }





////////////////////////////////////////////////////////////////////////////////////




// /*
//   ESP32-S3 + ILI9341 TFT LCD Example

//   https://wokwi.com/projects/343784047735997012
// */

// #include "SPI.h"
// #include "Adafruit_GFX.h"
// #include "Adafruit_ILI9341.h"

// #define TFT_DC 2
// #define TFT_CS 15
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// void setup() {
//   Serial.begin(115200); 
//   Serial.println("Welcome to Wokwi, ESP32-S3");
//   Wire.begin(10,8);
//   tft.begin();

//   tft.setCursor(44, 120);
//   tft.setTextColor(ILI9341_RED);
//   tft.setTextSize(3);
//   tft.println("ESP32-S3");
// }

// const uint32_t colors[] = {
//   ILI9341_GREEN,
//   ILI9341_CYAN,
//   ILI9341_MAGENTA,
//   ILI9341_YELLOW,
// };
// uint8_t colorIndex = 0;

// void loop() {
//   tft.setTextSize(2);
//   tft.setCursor(26, 164);
//   tft.setTextColor(colors[colorIndex++ % 4]);
//   tft.println("Welcome to Wokwi!");
//   delay(250);
// }











// /*
//   Adafruit LVGL Glue Example for pyportal (uses IL9341)
//   https://github.com/adafruit/Adafruit_LvGL_Glue/blob/master/examples/hello_pyportal/hello_pyportal.ino
// */
///////////////////////////////////

// Minimal "Hello" example for LittlevGL on Adafruit PyPortal. Requires
// LittlevGL, Adafruit_LvGL_Glue, Adafruit Touchscreen, Adafruit_GFX and
// Adafruit_ILI9341 (PyPortal, PyPortal Pynt) or Adafruit_HX8357 (PyPortal
// Titano) libraries. This example doesn't use any touchscreen input, but
// it's declared anyway so this sketch can be copied-and-pasted to serve
// as a starting point for other projects. If display is scrambled, check
// that the correct board is selected -- PyPortal vs PyPortal Titano.

// Prior Adafruit_LvGL_Glue users: see hello_changes example for updates!
#include "Arduino.h"

#include <SPI.h>
#include <Wire.h>

#define _ADAFRUIT_STMPE610H_
class Adafruit_STMPE610 {
  private:
    uint8_t spiIn();
    void spiOut(uint8_t x);

    TwoWire *_wire;
    SPIClass *_spi;
    int8_t _CS, _MOSI, _MISO, _CLK;
    uint8_t _i2caddr;

    int m_spiMode;

    
  public:
    Adafruit_STMPE610(uint8_t cspin, uint8_t mosipin,
                                        uint8_t misopin, uint8_t clkpin) {
      _CS = cspin;
      _MOSI = mosipin;
      _MISO = misopin;
      _CLK = clkpin;
    }
    Adafruit_STMPE610(uint8_t cspin, SPIClass *theSPI) {
      _CS = cspin;
      _MOSI = _MISO = _CLK = -1;
      _spi = theSPI;
    }
    Adafruit_STMPE610(TwoWire *theWire) {
      _CS = _MISO = _MOSI = _CLK = -1;
      _wire = theWire;
    }

};

// #include <Arduino.h>      // this is needed for FT6206
// #include <SPI.h>       // this is needed for display
#include <Adafruit_LvGL_Glue.h> // Always include this BEFORE lvgl.h!
#include <lvgl.h>
// #include <TouchScreen.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

// // The display also uses hardware SPI, plus #9 & #10
// #define TFT_CS 10
// #define TFT_DC 9
#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define TFT_ROTATION   3 // Landscape orientation on PyPortal
#define TFT_D0        34 // PyPortal TFT pins
#define TFT_WR        26
// #define TFT_DC        10
// #define TFT_CS        11
#define TFT_RST       24
#define TFT_RD         9
#define TFT_BACKLIGHT 6 // 25
#define YP            A4 // PyPortal touchscreen pins
#define XP            A5
#define YM            A6
#define XM            A7

// #if defined(ADAFRUIT_PYPORTAL_M4_TITANO)
//   #include <Adafruit_HX8357.h>
//   Adafruit_HX8357  tft(tft8bitbus, TFT_D0, TFT_WR, TFT_DC, TFT_CS, TFT_RST,
//     TFT_RD);
// #else
//   #include <Adafruit_ILI9341.h>
//   Adafruit_ILI9341 tft(tft8bitbus, TFT_D0, TFT_WR, TFT_DC, TFT_CS, TFT_RST,
//     TFT_RD);
// #endif

////Touch should come from i2c chip instead of analog pins(Adafruit_Touchscreen)
//TouchScreen        ts(XP, YP, XM, YM, 300);

Adafruit_LvGL_Glue glue;

// This example sketch's LittlevGL UI-building calls are all in this
// function rather than in setup(), so simple programs can just 
// copy-and-paste this sketch as a starting point, then embellish here:
void lvgl_setup(void) {
  // Create simple label centered on screen
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, "Hello Arduino!");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void setup(void) {
  Serial.begin(115200);

  // Initialize display BEFORE glue setup
  tft.begin();
  tft.setRotation(TFT_ROTATION);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);

  // PyPortal touchscreen needs no init

  // Initialize glue, passing in address of display & touchscreen
  LvGLStatus status = glue.begin(&tft, false);//, &ctp);
  if(status != LVGL_OK) {
    Serial.printf("Glue error %d\r\n", (int)status);
    for(;;);
  }

  lvgl_setup(); // Call UI-building function above
}

void loop(void) {
  lv_task_handler(); // Call LittleVGL task handler periodically
  delay(5);
}