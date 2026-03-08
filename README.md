# 🔌 Microcontrollers

Personal collection of firmware projects, experiments and prototypes for Arduino, ESP32, ESP8266 and other microcontroller platforms.

---

## 📁 Repository Structure

```
microcontrollers/
├── platforms/
│   ├── arduino/          # Arduino UNO, Mega, Nano...
│   ├── esp32/            # ESP32 projects
│   ├── esp8266/          # ESP8266 / NodeMCU projects
│   ├── stm32/            # STM32 projects
│   └── raspberry-pi-pico/
├── shared/
│   ├── libraries/        # Reusable custom libraries
│   ├── schemas/          # Circuit diagrams and schematics
│   └── docs/             # General documentation
└── tools/
    ├── scripts/          # Helper and flashing scripts
    └── configs/          # Build configurations
```

Each project follows this internal structure:

```
project-name/
├── README.md             # Wiring, dependencies, how to flash
├── src/                  # Source code
├── lib/                  # Project-specific libraries
├── include/              # Header files
└── docs/                 # Schematics, datasheets, notes
```

---

## 🛠️ Development Environment

- **IDE:** Arduino IDE 2.x
- **Languages:** C / C++
- **Platforms:** Arduino, ESP32, ESP8266

---

## ⚠️ Security Notice

Projects that use Wi-Fi, MQTT, or any external services store credentials in a local `secrets.h` file. This file is listed in `.gitignore` and is **never committed** to the repository.

Use the provided `secrets.example.h` in each project as a template.

---

## 📄 License

This repository is licensed under the [MIT License](LICENSE).

---

## 👤 Author

**Bruno Santos**  
GitHub: [@brunosantos](https://github.com/brunosantos)
