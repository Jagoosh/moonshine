#include <TimerOne.h>
#include <QuadDisplay.h>

// Troyka-QuadDisplay подключён к следующему пину:
#define quadPin A0

// TimerOne — доступны 9, 10, 11 пины;
// TimerThree — доступен 5 пин
// Управление высоким напряжением подключёно к следующему пину:
#define HTPin 11

// Troyka-Pot подключён к следующему пину:
#define sensorPin A2

int sensorValue = 0;
int blinkDuty = 12;

void setup() {
  // Настраиваем нужные контакты на выход
  pinMode(HTPin, OUTPUT);
  
  // Инициализируем TimerOne числом миллисекунд,
  // не имеющим общих делителей с 10000
  // (полупериод переменного тока),
  // но кратным 1023 (соответствует полному заполнению ШИМ)
  // 3 * 1023 == 3 * 3 * 11 * 31
  Timer1.initialize(1023 * 3);
  Timer1.pwm(HTPin, 0);
}

void dutyChange() {
  // Функция изменения скванжности при изменении данных датчика
  Timer1.setPwmDuty(HTPin, sensorValue * 102);
  blinkDuty = sensorValue;
  displayInt(quadPin, sensorValue);
}

void loop() {
  // Разбиваем диапазон датчика на 10 ступеней (1024 / 102 ≈ 10)
  sensorValue = analogRead(sensorPin) / 102;
  if (sensorValue != blinkDuty) {
    dutyChange();
  }
}
