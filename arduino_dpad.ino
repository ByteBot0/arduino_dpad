#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

//dpad input pin
int analogPin = 0;

//dpad analogRead value
int dpadInput = 0;

// To store analogRead(analogPin) value
int raw = 0;

// Pixel location
int vertical = 0;
int horizontal = 0;
int rotate = 0;

/*
Button layout:

   2         6
1     3
   4       5

*/
// Set button high and low values based on what R= is returning on the screen
bool button1; int button1Low = 624; int button1High = 650;

bool button2; int button2Low = 515; int button2High = 537;

bool button3; int button3Low = 223; int button3High = 233;

bool button4; int button4Low = 340; int button4High = 356;

bool button5; int button5Low = 60; int button5High = 66;

bool button6; int button6Low = 110; int button6High = 116;



void setup() {
  u8g2.begin();
}


void loop() {
  // clear the internal memory
  u8g2.clearBuffer();
  raw = analogRead(analogPin);

  // If button is in High-Low range then button click = true
  if ((raw >= button1Low) && (raw <= button1High)) {
    button1 = true;
  }
  if ((raw >= button2Low) && (raw <= button2High)) {
    button2 = true;
  }
  if ((raw >= button3Low) && (raw <= button3High)) {
    button3 = true;
  }
  if ((raw >= button4Low) && (raw <= button4High)) {
    button4 = true;
  }
  if ((raw >= button5Low) && (raw <= button5High)) {
    button5 = true;
  }
  if ((raw >= button6Low) && (raw <= button6High)) {
    button6 = true;
  }

// If button clicked then... Set button back to false when done
  if (button1 == true) {
    horizontal -= 10;
    button1 = false;
  }
    if (button2 == true) {
    vertical -= 10;
    button2 = false;
  }
    if (button3 == true) {
    horizontal += 10;
    button3 = false;
  }
    if (button4 == true) {
    vertical += 10;
    button4 = false;
  }
    if (button5 == true) {
    rotate += 1;
    button5 = false;
  }
    if (button6 == true) {
    vertical = 25;
    horizontal = 50;
    button6 = false;
  }

  //default snowman to test move
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontDirection(rotate);
  u8g2.drawGlyph(horizontal+60, vertical+35, 0x2603);

  // Print R= ...
  u8g2.setFont(u8g2_font_squeezed_b6_tr);
  u8g2.setFontDirection(0);
  u8g2.setCursor(3, 62);
  u8g2.print("R= ");
  u8g2.setCursor(15, 62);
  u8g2.print(raw);
  u8g2.sendBuffer();
  delay(1);

}
