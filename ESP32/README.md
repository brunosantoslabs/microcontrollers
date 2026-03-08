# 🔌 Microcontrollers

Personal collection of firmware projects, experiments and prototypes built with ESP32 and other microcontroller platforms.

---

## 📁 Repository Structure

```
microcontrollers/
├── platforms/
│   ├── esp32/                # ESP32 projects
│   │   ├── blink/            # [ESP32-1] LED blink — IDE validation
│   │   └── touch-led/        # [ESP32-2] Capacitive touch + LED
│   ├── arduino/
│   ├── esp8266/
│   └── raspberry-pi-pico/
├── shared/
│   ├── libraries/            # Reusable custom libraries
│   ├── schemas/              # Circuit diagrams and schematics
│   └── docs/                 # General documentation
├── .githooks/
│   └── prepare-commit-msg    # Conventional commit helper
└── tools/
    └── scripts/
```

Each project contains its own `README.md` with wiring, dependencies,
calibration notes and troubleshooting specific to that project.

---

## 🛠️ Development Environment

| Tool | Version / Detail |
|---|---|
| IDE | Arduino IDE 2.x |
| Board package | esp32 by Espressif Systems **v2.0.17** |
| Language | C / C++ |
| OS | Windows 11 |
| Serial port | COM5 (Silicon Labs CP2102) |

---

## ⚙️ Arduino IDE Setup

### 1 — Add ESP32 board support

`File → Preferences → Additional boards manager URLs`:
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

`Tools → Board → Boards Manager` → search `esp32` → install **esp32 by Espressif Systems**

> ⚠️ **Always install v2.0.17.** Version 3.x breaks the `touchRead()` API
> and may have other peripheral regressions.

### 2 — Board configuration

`Tools` menu — apply these settings for all ESP32 DOIT DevKit projects:

| Setting | Value |
|---|---|
| Board | `ESP32 Dev Module` |
| Upload Speed | `115200` |
| CPU Frequency | `240MHz` |
| Flash Size | `4MB (32Mb)` |
| Partition Scheme | `Default 4MB with spiffs` |
| Port | `COM5` |

### 3 — Upload tip

If upload hangs on `Connecting...`, hold the **BOOT** button on the board
and release it as soon as the upload starts.

---

## 🔌 Hardware — ESP32 DOIT DevKit

| Spec | Detail |
|---|---|
| Module | ESP32-WROOM-32D |
| USB chip | Silicon Labs CP2102 |
| Certification | Anatel (Brazil) |
| Driver | [CP210x Windows Drivers](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers) |
| Flash | 4MB |
| Onboard LED | GPIO2 (blue) |

### Pinout

```
                    ┌──────────┐
                    │   USB    │
               3V3  │          │  GND
               EN   │          │  GPIO23
            GPIO36  │          │  GPIO22
            GPIO39  │          │  GPIO1 (TX)
            GPIO34  │          │  GPIO3 (RX)
            GPIO35  │          │  GPIO21
            GPIO32  │          │  GND
            GPIO33  │          │  GPIO19
            GPIO25  │          │  GPIO18
            GPIO26  │          │  GPIO5
           GPIO27*  │          │  GPIO17
           GPIO14*  │          │  GPIO16
           GPIO12*  │          │  GPIO4*
               GND  │          │  GPIO0*
           GPIO13*  │          │  GPIO2   ← onboard blue LED
                    └──────────┘

* = capacitive touch capable pin (T4–T7 left, T0–T1 T3 right)
```

---

## 🔐 Security Notice

Projects that use Wi-Fi, MQTT, or external APIs store credentials in a
local `secrets.h` file. This file is listed in `.gitignore` and is
**never committed** to the repository.

Each such project provides a `secrets.example.h` as a template.

---

## 🪝 Git Hook — Conventional Commits

This repo includes a commit helper hook. After cloning, install it once:

```bash
cp .githooks/prepare-commit-msg .git/hooks/prepare-commit-msg
chmod +x .git/hooks/prepare-commit-msg
```

From then on, `git commit` will interactively prompt for task ID, type,
scope and description, and generate a properly formatted commit message.


## 📄 License

Apache License 2.0 — see [LICENSE](LICENSE)

## 👤 Author

**Bruno Santos**
