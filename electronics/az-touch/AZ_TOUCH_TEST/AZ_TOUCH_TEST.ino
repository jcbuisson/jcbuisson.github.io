
/*****************************
 * Important: see settings.h to configure your settings!!!
 * ***************************/
#include "settings.h"

#include <Arduino.h>
#include <SPI.h>

#include <XPT2046_Touchscreen.h>
#include "TouchControllerWS.h"
#include "ArialRounded.h"

/***
 * Install the following libraries through Arduino Library Manager
 * - Grafx by Daniel Eichhorn
 ***/
#include <MiniGrafx.h>
#include <ILI9341_SPI.h>


#define MINI_BLACK 0
#define MINI_WHITE 1
#define MINI_YELLOW 2
#define MINI_BLUE 3

// defines the colors usable in the paletted 16 color frame buffer
uint16_t palette[] = {ILI9341_BLACK, // 0
                      ILI9341_WHITE, // 1
                      ILI9341_YELLOW, // 2
                      0x7E3C
                      }; //3

int SCREEN_WIDTH = 240;
int SCREEN_HEIGHT = 320;
// Limited to 4 colors due to memory constraints
int BITS_PER_PIXEL = 2; // 2^2 =  4 colors


ILI9341_SPI tft = ILI9341_SPI(TFT_CS, TFT_DC, TFT_RST);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);


XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);
TouchControllerWS touchController(&ts);

void calibrationCallback(int16_t x, int16_t y);
CalibrationCallback calibration = &calibrationCallback;
  

void setup() {
  Serial.begin(115200);
  
  // switch TFT backlight on
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, LOW);    // HIGH to Turn on;
  
  gfx.init();
  gfx.fillBuffer(MINI_BLUE);
  gfx.commit();

  Serial.println("Initializing touch screen...");
  ts.begin();
}

void loop() {
  gfx.setColor(MINI_YELLOW);
  gfx.setFont(ArialRoundedMTBold_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 90, "https://thingpulse.com");

  gfx.setColor(1);
  gfx.fillCircle(20, 20, 10);
  gfx.commit();
}
