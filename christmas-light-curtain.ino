#define BUTTON_PIN 0
#define OUTPUT_PIN 2

#define MODES 9

#include <EEPROM.h>

int lastButtonState;
// OFF = 0, ... MAX = 8
int mode;

void nextMode() {
  digitalWrite(OUTPUT_PIN, LOW);
  delay(50);
  digitalWrite(OUTPUT_PIN, HIGH);
  delay(50);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(OUTPUT_PIN, OUTPUT);

  int temp = EEPROM.read(0);
  if (temp >= MODES || temp < 0) {
    mode = 0;
    EEPROM.write(0, mode);
  } else {
    mode = temp;
  }

  delay(1000);
  
  for (int i = 0; i < mode; mode++) {
    nextMode();
  }

  lastButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState != buttonState) {
    delay(50);

    if (lastButtonState == LOW && buttonState == HIGH) {
      nextMode();
      mode += 1;
      if (mode >= MODES) {
        mode = 0;
      }
      EEPROM.write(0, mode);
    }

    lastButtonState = buttonState;
  }
}
