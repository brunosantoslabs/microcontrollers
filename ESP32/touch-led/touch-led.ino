// =============================================================
// ESP32 Capacitive Touch Reader with LED Control
// Author: Bruno Santos
// Task: ESP32-2
// Board: ESP32 DOIT DevKit - WROOM-32D
// SDK: arduino-esp32 v2.0.17
//
// Behavior:
//   - Reads capacitive touch value from GPIO4 (T0)
//   - LED on GPIO2 turns ON when touch is detected
//   - LED turns OFF when touch is released
//
// Touch API (v2.x):
//   - Untouched: ~60–80
//   - Touched:   ~8–20
//   - Trigger condition: value BELOW threshold
// =============================================================

// -- Pin definitions ------------------------------------------
#define TOUCH_PIN       T0    // GPIO4 — capacitive touch input
#define LED_PIN         2     // GPIO2 — onboard blue LED

// -- Touch sensitivity ----------------------------------------
// Lower value = less sensitive (harder to trigger)
// Higher value = more sensitive (easier to trigger)
// Recommended starting point: 30
#define TOUCH_THRESHOLD 70

// -- Serial baud rate -----------------------------------------
#define BAUD_RATE       115200

// -------------------------------------------------------------
void setup() {
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("==============================================");
    Serial.println(" ESP32 Capacitive Touch Reader — ESP32-2");
    Serial.println("==============================================");
    Serial.print  ("  Touch pin  : GPIO4 (T0)\n");
    Serial.print  ("  LED pin    : GPIO2\n");
    Serial.print  ("  Threshold  : ");
    Serial.println(TOUCH_THRESHOLD);
    Serial.println("  Touch the GPIO4 pin to trigger the LED.");
    Serial.println("----------------------------------------------");
}

// -------------------------------------------------------------
void loop() {
    int touchValue = touchRead(TOUCH_PIN);

    // Print current touch value for calibration
    Serial.print("Touch value: ");
    Serial.print(touchValue);

    if (touchValue < TOUCH_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("  >> TOUCHED — LED ON");
    } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("  -- released");
    }

    delay(100);
}