class CapacitiveKey {
  public:
    CapacitiveSensor* sensor;
    bool keyReleased = true;
    char key;
    unsigned int releaseDelay = 50;
    unsigned long releaseTimer;
    unsigned int treshold;  
    int led;
    unsigned int sample;
    CapacitiveKey(uint8_t sendPin, uint8_t receivePin, int statusLED, unsigned int capacitiveTreshold, char keyboardKey)  {
      sensor = new CapacitiveSensor(sendPin, receivePin);
      treshold = capacitiveTreshold;
      key = keyboardKey;
      led = statusLED;
      pinMode(led, OUTPUT);
    }
    ~CapacitiveKey() {
      delete sensor;
    }
    void keyUpdate(bool keyboardActive) {
      sample = sensor->capacitiveSensorRaw(1);
      if (sample > treshold) {
        if (keyReleased) {
          analogWrite(led, 5);
          if (keyboardActive) Keyboard.press(key);
          keyReleased = false;
        }
        releaseTimer = millis();
      }
      else {
        if (!keyReleased) {
          if (millis() - releaseTimer >= releaseDelay && releaseTimer != 0) {
            analogWrite(led, 0);
            Keyboard.release(key);
            keyReleased = true;
            releaseTimer = 0;
          }
        }
      }
    }
};
