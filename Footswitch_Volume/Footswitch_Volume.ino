//www.elegoo.com
//2016.12.12

#include "Stepper.h"

#define SWITCH_PIN 7

/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);

void setup()
{ 
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop()
{
  static int chordVolume = 0;
  static int desiredChordVolume = 0;
  int switchState = digitalRead(SWITCH_PIN);
  small_stepper.setSpeed(900); //Max seems to be 500^H^H^H900
  if (switchState == LOW) {
    desiredChordVolume = 1024;
  } else {
    desiredChordVolume = 0;
  }
  Steps2Take = desiredChordVolume - chordVolume;
  small_stepper.step(Steps2Take);
  chordVolume = desiredChordVolume;
  delay(1000);
}
