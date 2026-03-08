// Author: Bruno Santos
// Blink LED example for ESP32 DOIT DevKit V1 (ESP32-WROOM-32D)
// Board: DOIT ESP32 DevKit V1
// Built-in LED: GPIO 2

const int ledPin = 2; // Built-in LED on ESP32 DOIT DevKit V1

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
