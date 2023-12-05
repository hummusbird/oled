#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(3);
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();

  Serial.begin(115200);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, "gaming");
  u8g2.sendBuffer();
}

void loop(void) {
  // recvOneChar();
  printToDisplay();
}

void printToDisplay() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.drawStr(0, 60, "hi chat");
    u8g2.drawStr(60, 60, "@miaowing");
  u8g2.setFont(u8g2_font_logisoso34_tf);
  u8g2.drawStr(20, 60, ">~<");

  u8g2.sendBuffer();
}