#include <QuadDisplay2.h>

constexpr uint8_t POTENTIOMETER_PIN = A2;
constexpr uint8_t LED_PIN = A3;
constexpr uint8_t BUZZER_PIN = 7;
constexpr uint8_t Q_DISPLAY_PIN = 10;
constexpr uint8_t BUTTON_PIN = 11;

QuadDisplay qd(Q_DISPLAY_PIN);

void setup() {
  pinMode(POTENTIOMETER_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN , OUTPUT);
  qd.begin();
  qd.displayClear();
}

void loop() {
  uint16_t rotation = analogRead(POTENTIOMETER_PIN);
  uint8_t getValuePotentiometr = map(rotation, 0, 1023, 60, 0);
  //qd.displayInt(getValuePotentiometr);
  for (uint8_t britnes = 0; britnes < 21; britnes++) {
    analogWrite(LED_PIN, britnes);
    delay(100);
  }
  for (uint8_t britnes = 20; britnes > 0; britnes--) {
    analogWrite(LED_PIN, britnes);
    delay(100);
  }
}
