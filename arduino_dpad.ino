#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

//dpad input pin
int analogPin = 0;

// To store analogRead(analogPin) value
int raw = 0;

// Pixel location
int vertical = 35;
int horizontal = 60;
int rotate = 0;

/*
Button layout:

   2         6
1     3
   4       5

*/
// Set button high and low values based on what R= is returning on the screen or serial monitor
bool button1; int button1Low = 624; int button1High = 650;

bool button2; int button2Low = 515; int button2High = 537;

bool button3; int button3Low = 223; int button3High = 233;

bool button4; int button4Low = 340; int button4High = 356;

bool button5; int button5Low = 60; int button5High = 66;

bool button6; int button6Low = 110; int button6High = 116;



void setup() {
  u8g2.begin();
  Serial.begin(9600);
}


void loop() {
  u8g2.clearBuffer(); // clear the internal memory
  raw = analogRead(analogPin);

  // If button is in High-Low range then move
  if ((raw >= button1Low) && (raw <= button1High)) {
    horizontal -= 10;
  }
  if ((raw >= button2Low) && (raw <= button2High)) {
    vertical -= 10;
  }
  if ((raw >= button3Low) && (raw <= button3High)) {
    horizontal += 10;
  }
  if ((raw >= button4Low) && (raw <= button4High)) {
    vertical += 10;
  }
  if ((raw >= button5Low) && (raw <= button5High)) {
    rotate += 1;
  }
  if ((raw >= button6Low) && (raw <= button6High)) {
    vertical = 25;
    horizontal = 50;
  }
  
  // Prevent snowman from exploding. Comment out if you'd like
  if (rotate == 4) {
    rotate = 0;
  }

  //default snowman to test move
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontDirection(rotate);
  u8g2.drawGlyph(horizontal, vertical, 0x2603);

  // Print R= ... on screen
  u8g2.setFontDirection(0);
  u8g2.setCursor(3, 62);
  u8g2.print("R= ");
  u8g2.setCursor(20, 62);
  u8g2.print(raw);
  u8g2.sendBuffer();
  
  // Print to serial to use without screen
  Serial.print("Raw: ");
  Serial.println(raw);
   
  delay(100);

}
