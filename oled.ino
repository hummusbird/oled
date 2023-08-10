#include <U8g2lib.h>
#include <Wire.h>

// U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// void u8g2_prepare() {
//   u8g2.setFont(u8g2_font_profont11_tf);
//   u8g2.setFontRefHeightExtendedText();
//   u8g2.setDrawColor(1);
//   u8g2.setFontPosTop();
//   u8g2.setFontDirection(0);
// }

int len = 400;

char receivedChar;
int timestamps[400];
int count = 0;
int head = 0;
int tail = 0;

int WPM = 0;
unsigned long lastTimestamp = 0;

void push(char t) {
  timestamps[head] = t;
  count++;
  if (head == len) {
    head = 0;
  } else {
    head++;
  }
}

int peek() {
  return timestamps[tail];
}

int pop() {
  if (head == tail) {
    return -1;
  } else {
    int ctail = tail;
    count--;
    if (tail == len) {
      tail = 0;
    } else {
      tail++;
    }

    return timestamps[ctail];
  }
}

void setup(void) {
  // u8g2.begin();
  // u8g2_prepare();

  Serial.begin(115200);
}

void loop(void) {
  recvOneChar();
  calculateWPM();
  printToDisplay();
}

void recvOneChar() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if ((int)receivedChar != 10) {
      if (receivedChar == 'N') {
        Serial.println(peek());
      } else if (receivedChar == 'P') {
        Serial.println(pop());
      } else {
        push(millis() / 500);
      }
    }
  }
}

void printToDisplay() {
  Serial.print("WPM: ");
  Serial.println(WPM);
  Serial.print("MILLI: ");
  Serial.println(peek());
  // u8g2.clearBuffer();
  // u8g2.setFont(u8g2_font_profont11_tf);
  // u8g2.drawStr(0, 0, "WPM:");
  // u8g2.setFont(u8g2_font_logisoso34_tf);
  // u8g2.drawStr(0, 20, String(WPM).c_str());
  // u8g2.sendBuffer();
}

void calculateWPM() {
  if (lastTimestamp < millis() - 200) {
    while ((lastTimestamp / 500) - 12 > peek() && peek() != 0) {
      pop();
    }
    lastTimestamp = millis();
  }

  WPM = count;
}
