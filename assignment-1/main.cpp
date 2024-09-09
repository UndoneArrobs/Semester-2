#include <Arduino.h>

// Define constants for pin numbers, delay times, and threshold values
#define ANALOG_PIN A0
#define LED_PIN 3
#define MEDIUM_DELAY 500
#define SHORT_DELAY 250
#define VERY_SHORT_DELAY 100
#define THRESHOLD_HIGH 450
#define THRESHOLD_MEDIUM_HIGH 335
#define THRESHOLD_MEDIUM_LOW 200
#define THRESHOLD_LOW 100



int delayTime = 1000;
unsigned long lastTime = 0;

void activateLed(int value) {
  unsigned long currentTime = millis();
  unsigned long diffTime = currentTime - lastTime;
  delayTime = 0;

  if (value < THRESHOLD_HIGH && value > THRESHOLD_MEDIUM_HIGH) {
    delayTime = MEDIUM_DELAY;
  }
  else if (value < THRESHOLD_MEDIUM_HIGH && value > THRESHOLD_MEDIUM_LOW) {
    delayTime = SHORT_DELAY;
  }
  else if (value < THRESHOLD_MEDIUM_LOW && value > THRESHOLD_LOW) {
    delayTime = VERY_SHORT_DELAY;
  }

  if (diffTime >= delayTime) {
    lastTime = currentTime;
    if (delayTime == 0) {
      digitalWrite(LED_PIN, LOW);
    }
    else {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ANALOG_PIN, INPUT);
}

void loop() {
  int analogValue = analogRead(ANALOG_PIN);
  activateLed(analogValue);
}