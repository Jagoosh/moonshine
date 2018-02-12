#include <QuadDisplay.h>
#include <TimerThree.h>

#define quadPin A0
#define clapanPin 4
#define clapanPot A2

int clapanErr = 0;
int clapanCount = 0;

void setup() {
  pinMode(clapanPin, OUTPUT);
  Timer3.initialize(1000000);
  Timer3.attachInterrupt(bresenham);
}

void bresenham() {
  clapanErr = clapanErr + analogRead(clapanPot);
  if (clapanErr >= 512) {
    digitalWrite(clapanPin, HIGH);
    clapanErr = clapanErr - 1023;
    ++clapanCount;
  }
  else
  {
    digitalWrite(clapanPin, LOW);
  }
  displayInt(quadPin, clapanCount);
}

void loop() {
  
}
