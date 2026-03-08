# ESP32-2 — Capacitive Touch Reader with LED Control

**Author:** Bruno Santos  
**Board:** ESP32 DOIT DevKit — ESP32-WROOM-32D  
**Path:** `platforms/esp32/touch-led/`

---

## What This Does

Reads the capacitive touch sensor on GPIO4 (T0). When a finger touches the pin,
the value drops below the configured threshold and the onboard blue LED on GPIO2
turns on. Releasing the pin turns the LED off.

This project teaches: analog pin reading, threshold-based logic, and touch
sensor calibration.

---

## Hardware

No external components required. Touch is detected by placing a finger directly
on the **GPIO4 header pin** — 4th pin from the bottom on the right side of the board.

| Pin | Role |
|---|---|
| GPIO4 (T0) | Capacitive touch input — touch here with finger |
| GPIO2 | Onboard blue LED output |

```
Right side of board, counting from bottom:

  1st  →  GPIO15
  2nd  →  GPIO2   (blue LED)
  3rd  →  GPIO0
  4th  →  GPIO4   ← touch here ★
```

---

## How It Works

The ESP32 measures capacitance on the pin. A human finger increases the
capacitance, which causes the raw `touchRead()` value to **decrease**.

| State | Value (this board) |
|---|---|
| Idle — no touch | ~113 |
| Finger on pin | ~49 |
| Threshold | **70** |

When `touchRead(T0) < 70` → LED on. Otherwise → LED off.

---

## SDK Version — Critical

| Version | Touch behavior |
|---|---|
| **v2.0.17** ✅ | Values ~60–130 idle, drop on touch — works correctly |
| v3.x ❌ | Values ~1900, completely unresponsive to touch |

Always use **arduino-esp32 v2.0.17** for this project.

---

## Source Code

```cpp
// =============================================================
// ESP32 Capacitive Touch Reader with LED Control
// Author: Bruno Santos
// Task: ESP32-2
// Board: ESP32 DOIT DevKit - WROOM-32D
// SDK: arduino-esp32 v2.0.17
//
// Touch API (v2.x): touched = value BELOW threshold
//   Idle:    ~113
//   Touched: ~49
// =============================================================

#define TOUCH_PIN       T0      // GPIO4 — 4th pin from bottom, right side
#define LED_PIN         2       // onboard blue LED
#define TOUCH_THRESHOLD 70      // between idle (~113) and touched (~49)
#define BAUD_RATE       115200

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

void loop() {
    int touchValue = touchRead(TOUCH_PIN);

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
```

---

## Calibrating the Threshold

1. Upload the code and open Serial Monitor at **115200 baud**
2. Note the idle value (no touch)
3. Touch GPIO4 and note the minimum value reached
4. Set `TOUCH_THRESHOLD` to the midpoint between the two

```
Example: idle = 113, touched = 49 → threshold = (113 + 49) / 2 ≈ 70
```

---

## Troubleshooting

| Symptom | Cause | Fix |
|---|---|---|
| Values around 1900, no response | arduino-esp32 v3.x | Downgrade to v2.0.17 |
| LED always ON | Threshold too high | Lower `TOUCH_THRESHOLD` |
| LED never triggers | Threshold too low | Raise `TOUCH_THRESHOLD` |
| Upload hangs on `Connecting...` | Board not in flash mode | Hold BOOT button until upload starts |

---

## Concepts Learned

- `touchRead(pin)` measures raw capacitance — lower value = more capacitance = finger present
- Threshold must be calibrated per board and environment
- arduino-esp32 SDK version critically affects peripheral APIs
- GPIO2 is the onboard LED **and** a touch-capable pin (T2) — avoid using it for touch

---

## Next

`[ESP32-3] Connect ESP32 to Wi-Fi network and display assigned IP on Serial Monitor`
