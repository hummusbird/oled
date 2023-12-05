#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontDirection(3);
  u8g2.setFontPosTop();
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();

  Serial.begin(9600);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 60, "init...");
  delay(1000);
  u8g2.sendBuffer();

  printToDisplay();
}

void loop(void) { 
}

void printToDisplay() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.drawStr(0, 59, "miaow.ing");
  u8g2.drawStr(110, 59, "@miaowing");
  u8g2.setFont(u8g2_font_logisoso34_tf);
  u8g2.drawStr(40, 64, ">~<");

  u8g2.sendBuffer();
}