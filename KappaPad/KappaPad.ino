#include <CapacitiveSensor.h>
#include <Keyboard.h>

#include "CapacitiveKey.h"

//#define SERIAL_OUTPUT
#define DISABLE_PIN 12

void setup() {
  #ifdef SERIAL_OUTPUT
  Serial.begin(115200);
  #endif
  Keyboard.begin();
  pinMode(DISABLE_PIN, INPUT_PULLUP);
}

CapacitiveKey key0 = CapacitiveKey(
  7,    //Capacitive Send Pin
  2,    //Capacitive Sense Pin
  6,    //LED Pin
  26,   //Capacitive Threshold
  'd',  //Keyboard Key
  0     //LED Brightness (0-255)
);
CapacitiveKey key1 = CapacitiveKey(
  8,    //Capacitive Send Pin
  13,   //Capacitive Sense Pin
  11,   //LED Pin
  26,   //Capacitive Threshold
  'f',  //Keyboard Key
  0     //LED Brightness (0-255)
);

void loop() {
  bool keyboardActive = digitalRead(DISABLE_PIN);
  key0.keyUpdate(keyboardActive);
  key1.keyUpdate(keyboardActive);

  #ifdef SERIAL_OUTPUT
  Serial.print(key0.sample);
  Serial.print(",");
  Serial.println(key1.sample);
  #endif
}
