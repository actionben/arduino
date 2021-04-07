#include "pitches.h"

#define BUTTON_PIN 11
#define SYNC_PIN_R 12
#define SYNC_PIN_L 10
#define PULSE_DURATION 2.5

unsigned int interval = 1000;

unsigned int bpmToMs(unsigned int bpm) {
  return 60000 / bpm;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SYNC_PIN_R, OUTPUT);
  pinMode(SYNC_PIN_L, OUTPUT);

  // set interval to desired BPM
  interval = bpmToMs(64) / 4;
}

void loop() {
  static bool go = false;
  int buttonState = digitalRead(BUTTON_PIN);
  static int currentBeat = 1;
  if (buttonState == 0) {
    currentBeat = 1;
  }
  if (buttonState == 1) {
    if(currentBeat % 2 == 1) {
      if(currentBeat <= 16) {
        digitalWrite(SYNC_PIN_R, HIGH);
      } else if(currentBeat <= 32) {
        tone(SYNC_PIN_R, NOTE_C5, PULSE_DURATION * 10);
      } else {
        digitalWrite(SYNC_PIN_L, HIGH);
      }
    }
    delay(PULSE_DURATION);
    digitalWrite(SYNC_PIN_R, LOW);
    digitalWrite(SYNC_PIN_L, LOW);
    delay(interval - PULSE_DURATION);
    currentBeat+=1;
  }
}
