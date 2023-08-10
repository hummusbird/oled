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

int len = 1000;
int count = 0;

char receivedChar;
char timestamps[1000];
int head = 0;
int tail = 0;

int WPM = 0;
unsigned long lastTimestamp = 0;

void push(char t) {
  timestamps[head] == t;
  count++;

  if (head == len) {
    head = 0;
  } else {
    head++;
  }
}

char peek() {

  Serial.write("TAIL: ");
  Serial.println(tail);

  Serial.write("HEAD: ");
  Serial.println(head);

  Serial.write("QUEUE TAIL: ");
  Serial.println(timestamps[tail]);

  Serial.write("QUEUE HEAD: ");
  Serial.println(timestamps[head]);

  return timestamps[tail];
}

char pop() {
  if (head == tail) {
    return -1;
  } else {
    count--;
    int ctail = tail;

    if (tail == len) {
      tail = 0;
    } else {
      tail++;
    }

    return timestamps[ctail];
  }
}

void setup(void) {
  u8g2.begin();
  u8g2_prepare();

  Serial.begin(115200);

  u8g2.clearBuffer();
  u8g2.drawStr(0, 0, "init...");
  u8g2.sendBuffer();
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
      if (receivedChar == 'C') {
        Serial.write("COUNT: ");
        Serial.println(count);
      }

      else if (receivedChar == 'N') {
        peek();
      }

      else if (receivedChar == 'P') {
        pop();
      }

      else {
        push(receivedChar);
        Serial.write("char: ");
        Serial.println(receivedChar);
      }
    }
  }
}

void printToDisplay() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_profont11_tf);
  u8g2.drawStr(0, 0, "WPM:");
  u8g2.setFont(u8g2_font_logisoso34_tf);
  u8g2.drawStr(0, 20, String(WPM).c_str());
  u8g2.sendBuffer();
}

void calculateWPM() {
  // Serial.write("millis:");
  // Serial.println(millis());

  if (lastTimestamp < millis() - 1000 && (int)receivedChar != 10) {
    lastTimestamp = millis();
  }

  WPM = 0;
}
