class CapacitiveKey
{
  public:
    CapacitiveSensor* sensor;
    bool keyReleased = true;
    char key;
    unsigned int releaseDelay = 50;
    unsigned long releaseTimer;
    unsigned int threshold;  
    int led;
    unsigned int sample;
    unsigned int ledBrightness;
    CapacitiveKey(uint8_t sendPin,
                  uint8_t receivePin,
                  int statusLED,
                  unsigned int capacitiveThreshold,
                  char keyboardKey,
                  unsigned int ledBrightness)
    {
      sensor = new CapacitiveSensor(sendPin, receivePin);
      threshold = capacitiveThreshold;
      key = keyboardKey;
      led = statusLED;
      pinMode(led, OUTPUT);
    }
    ~CapacitiveKey()
    {
      delete sensor;
    }
    void keyUpdate(bool keyboardActive)
    {
      sample = sensor->capacitiveSensorRaw(1);
      if (sample > threshold) {
        if (keyReleased) {
          analogWrite(led, ledBrightness);
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
