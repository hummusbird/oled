#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

const int bufferSize = 24;

long times[bufferSize];
int idx;

char receivedChar;

void addTime(long time) {
  times[idx] = time;
  idx = (idx + 1) % bufferSize;
}

float checkAverage() {
  int i = 0;
  float effectiveBufferSize = bufferSize;
  while (times[(idx + i) % bufferSize] < (millis() - 1000 * 8) && i < bufferSize) {
    i++;
    effectiveBufferSize -= 1;
  }

  return (effectiveBufferSize / (millis() - times[(idx + i) % bufferSize])) * 1000.0 * 60.0 * 0.2;
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();

  Serial.begin(9600);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, "WPM:");
  u8g2.sendBuffer();

  for (int i = 0; i < bufferSize; i++) {
    times[i] = -30000;
  }
}

void loop(void) {
  recvOneChar();
  printToDisplay();
}

void recvOneChar() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if ((int)receivedChar != 10) {
      addTime(millis());
    }
  }
}

void printToDisplay() {
  // Serial.print("WPM: ");
  // Serial.println(WPM);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.drawStr(0, 0, "WPM:");
  u8g2.setFont(u8g2_font_logisoso34_tf);
  u8g2.drawStr(0, 20, String((int)checkAverage()).c_str());
  u8g2.sendBuffer();
}