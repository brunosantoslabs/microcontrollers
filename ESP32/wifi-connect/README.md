# ESP32-3 — Wi-Fi Connect

**Author:** Bruno Santos  
**Board:** ESP32 DOIT DevKit — ESP32-WROOM-32D  
**Path:** `platforms/esp32/wifi-connect/`

---

## What This Does

Connects the ESP32 to a Wi-Fi network and prints the assigned IP address,
MAC address and signal strength (RSSI) to the Serial Monitor. Automatically
attempts to reconnect if the connection is lost.

---

## Hardware

No external components required. Uses the ESP32's built-in Wi-Fi radio.

| Spec | Detail |
|---|---|
| Module | ESP32-WROOM-32D |
| Wi-Fi | 802.11 b/g/n — 2.4GHz |
| MAC Address | 00:4B:12:06:8E:BC |

---

## Project Structure

```
wifi-connect/
├── wifi-connect.ino      # Main firmware
├── secrets.h             # Wi-Fi credentials — NOT committed
└── secrets.example.h     # Credentials template — committed
```

---

## Setup

### 1 — Create your credentials file

Copy `secrets.example.h` to `secrets.h` and fill in your network details:

```cpp
#define WIFI_SSID     "your_network_name"
#define WIFI_PASSWORD "your_network_password"
```

> `secrets.h` is listed in `.gitignore` and will **never** be committed.

### 2 — Board configuration

| Setting | Value |
|---|---|
| Board | `ESP32 Dev Module` |
| Upload Speed | `115200` |
| Port | `COM5` |
| SDK | arduino-esp32 **v2.0.17** |

### 3 — Open Serial Monitor

`Tools → Serial Monitor` — set baud rate to **115200**.  
After uploading, press the **EN** button on the board to reset and see output.

---

## Expected Serial Monitor Output

```
==============================================
 ESP32 Wi-Fi Connect — ESP32-3
==============================================
  Connecting to: your_network
  ......
----------------------------------------------
  Connected!
  IP Address   : 192.168.0.75
  MAC Address  : 00:4B:12:06:8E:BC
  Signal (RSSI): -55 dBm
==============================================
```

Each `.` represents a 500ms retry attempt. A good connection typically
resolves in 1–3 dots.

---

## RSSI Reference

| RSSI | Signal Quality |
|---|---|
| -30 to -50 dBm | Excellent |
| -50 to -60 dBm | Good ✅ |
| -60 to -70 dBm | Fair |
| Below -70 dBm | Weak |

Measured signal on this board: **-55 dBm** (good).

---

## Source Code

```cpp
// =============================================================
// ESP32 Wi-Fi Connect — Display IP on Serial Monitor
// Author: Bruno Santos
// Task: ESP32-3
// Board: ESP32 DOIT DevKit - WROOM-32D
// SDK: arduino-esp32 v2.0.17
// =============================================================

#include <WiFi.h>
#include "secrets.h"

#define BAUD_RATE       115200
#define RETRY_DELAY_MS  500

void setup() {
    Serial.begin(BAUD_RATE);
    delay(1000);

    Serial.println("==============================================");
    Serial.println(" ESP32 Wi-Fi Connect — ESP32-3");
    Serial.println("==============================================");
    Serial.print("  Connecting to: ");
    Serial.println(WIFI_SSID);
    Serial.print("  ");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(RETRY_DELAY_MS);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("----------------------------------------------");
    Serial.println("  Connected!");
    Serial.print  ("  IP Address   : ");
    Serial.println(WiFi.localIP());
    Serial.print  ("  MAC Address  : ");
    Serial.println(WiFi.macAddress());
    Serial.print  ("  Signal (RSSI): ");
    Serial.print  (WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("==============================================");
}

void loop() {
    // Reconnect automatically if connection is lost
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("  Connection lost. Reconnecting...");
        WiFi.reconnect();

        while (WiFi.status() != WL_CONNECTED) {
            delay(RETRY_DELAY_MS);
            Serial.print(".");
        }

        Serial.println();
        Serial.print("  Reconnected! IP: ");
        Serial.println(WiFi.localIP());
    }

    delay(5000);
}
```

---

## Troubleshooting

| Symptom | Cause | Fix |
|---|---|---|
| Serial Monitor blank | Missed setup() output | Press EN button to reset |
| Dots never stop | Wrong SSID or password | Double-check `secrets.h` |
| Dots never stop | 5GHz network | ESP32 only supports 2.4GHz |
| Compilation error: secrets.h not found | File missing | Copy `secrets.example.h` → `secrets.h` |
| Nothing in Serial Monitor | Wrong baud rate | Set to 115200 in Serial Monitor |

> **Note:** ESP32 only connects to **2.4GHz** networks. If your router
> broadcasts both 2.4GHz and 5GHz under the same name, the ESP32 will
> connect to the 2.4GHz band automatically.

---

## Concepts Learned

- `WiFi.begin()` initiates the connection asynchronously — polling with `WiFi.status()` is required
- `WiFi.localIP()` returns the DHCP-assigned IP address
- `WiFi.RSSI()` returns signal strength in dBm — more negative = weaker signal
- Credentials must be kept in `secrets.h` and excluded from version control
- Serial Monitor must be open **before** reset to catch `setup()` output

---

## Next Task

`[ESP32-4] Implement HTTP GET request over Wi-Fi with Serial Monitor response logging`
