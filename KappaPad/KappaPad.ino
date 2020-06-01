

#include <CapacitiveSensor.h>
#include <Keyboard.h>

#include "capacitiveKey.h"

//#define SERIAL_OUTPUT
#define DISABLE_PIN 15

void setup() {
  #ifdef SERIAL_OUTPUT
  Serial.begin(115200);
  #endif
  Keyboard.begin();
  pinMode(DISABLE_PIN, INPUT_PULLUP);
}

CapacitiveKey key0 = CapacitiveKey(
  2,    //Capacitive Send Pin
  4,    //Capacitive Sense Pin
  6,    //LED Pin
  15,    //Capacitive Treshold
  'x'  //Keyboard Key
);
CapacitiveKey key1 = CapacitiveKey(
  3,    //Capacitive Send Pin
  8,    //Capacitive Sense Pin
  10,   //LED Pin
  16,    //Capacitive Treshold
  'z'  //Keyboard Key
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

// delay(1);
}
