// =============================================================
// ESP32 Wi-Fi Connect — Display IP on Serial Monitor
// Author: Bruno Santos
// Task: ESP32-3
// Board: ESP32 DOIT DevKit - WROOM-32D
// SDK: arduino-esp32 v2.0.17
//
// Connects to Wi-Fi and prints the assigned IP address.
// Retries indefinitely until connection is established.
// =============================================================

#include <WiFi.h>
#include "secrets.h"

#define BAUD_RATE       115200
#define RETRY_DELAY_MS  500

// -------------------------------------------------------------
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

// -------------------------------------------------------------
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