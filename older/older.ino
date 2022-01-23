#include "pitches.h"

#define BUTTON_PIN 11
#define TEMPO_PIN 7
#define COUNT_IN_PIN 6
#define PO_12_PIN 5
#define PO_128_PIN 4
#define PULSE_DURATION 2.5
#define COUNT_IN 8

unsigned int interval = 1000;

unsigned int bpmToMs(unsigned int bpm) {
  return 60000 / bpm;
}

unsigned int currentVerse(unsigned int beat) {
  return (((beat - COUNT_IN) -1) / 32) + 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TEMPO_PIN, OUTPUT);
  pinMode(COUNT_IN_PIN, OUTPUT);
  pinMode(PO_12_PIN, OUTPUT);
  pinMode(PO_128_PIN, OUTPUT);

  // set interval to desired BPM
  interval = bpmToMs(60) / 2;
}

void loop() {
  static bool go = false;
  int buttonState = digitalRead(BUTTON_PIN);
  static int currentBeat = 1;
  static int verse = 0;
  if (buttonState == 0) {
    currentBeat = 1;
  }
  if (buttonState == 1) {
    if(currentBeat <= COUNT_IN / 2) {
      digitalWrite(COUNT_IN_PIN, HIGH);
    } else if(currentBeat <= COUNT_IN) {
      tone(COUNT_IN_PIN, NOTE_D4, PULSE_DURATION * 5);
    } else {
      digitalWrite(TEMPO_PIN, HIGH);
      verse = currentVerse(currentBeat);
      if(verse == 3 || verse == 5 || verse == 7) {
        digitalWrite(PO_12_PIN, HIGH);
      }
      if(verse == 2 || verse == 4 || verse == 6 || verse == 7) {
        digitalWrite(PO_128_PIN, HIGH);
      }
    }
    delay(PULSE_DURATION);
    digitalWrite(TEMPO_PIN, LOW);
    digitalWrite(COUNT_IN_PIN, LOW);
    digitalWrite(PO_12_PIN, LOW);
    digitalWrite(PO_128_PIN, LOW);
    delay(interval - PULSE_DURATION);
    currentBeat+=1;
  }
}
