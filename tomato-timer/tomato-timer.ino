#include <QuadDisplay2.h>                                               // подключение библиотеки дисплея

constexpr uint8_t POTENTIOMETER_PIN = A0;                               // аналоговый пин, к которому подключен потенциометр
constexpr uint8_t BUTTON_PIN = 4;                                       // цифровой пин, к которому подключена кнопка
constexpr uint8_t BUZZER_PIN = 7;                                       // цифровой пин, к которому подключена пищалка
constexpr uint8_t QUAD_DISPLAY_PIN = 9;                                 // цифровой пин, к которому подключен дисплей

constexpr uint32_t minuteTime = 60000;                                  // частота обновления таймера в одну минуту

QuadDisplay qd(QUAD_DISPLAY_PIN);                                       // объект для работы с дисплеем

uint32_t timeCalculation = 0;                                           // переменная для подсчёта времени
uint16_t reverseTimer;                                                  // переменная для хранения таймера

void setup() {
  qd.begin();                                                           // инициализация дисплея
  settingTimer();                                                       // функция установки таймера
}

void loop() {
  if ((reverseTimer > 0) && ((millis() - prevMillis) > minuteTime)) {   // если время таймера не дошло до нуля и прошла 1 секунда
    qd.displayInt(--reverseTimer);                                      // выводим значение на дисплей
    prevMillis = millis();                                              // запоминаем текущее время
    if (reverseTimer == 0) {                                            // если таймер дошёл до нуля
      qd.displayDigits(QD_NONE, QD_O, QD_f, QD_f);                      // подаём звуковой сигнал и выводим «Off» на дисплей
      tone(BUZZER_PIN, 4000, 200);
    }
  }

  if (!digitalRead(BUTTON_PIN)) {                                       // если нажата кнопка
    tone(BUZZER_PIN, 500, 500);                                         // подаём звуковой сигнал
    delay(1000);
    settingTimer();                                                     // выполняем настройку таймера
  }
}

void settingTimer(){                                                    // функция настройки таймера
  // пока кнопка не нажата
  while (digitalRead(BUTTON_PIN)) {
    reverseTimer = analogRead(POTENTIOMETER_PIN);                       // считываем значения с потенциометра
    reverseTimer = map(reverseTimer, 1023, 0, 0, 180);                  // задаём предельный диапазон таймера
    qd.displayInt(reverseTimer);                                        // и выводим его на дисплей
    delay(30);
  }
  // после нажатия кнопки, подаём звуковой сигнал
  tone(BUZZER_PIN, 2000, 200);
  delay(300);
  tone(BUZZER_PIN, 3000, 200);
  delay(300);
  tone(BUZZER_PIN, 4000, 200);
}