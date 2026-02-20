# ESPHome Notes

## MQTT

Do NOT add MQTT to ESP8266 devices (Sonoff S31, Shelly1, Athom smart plugs). The firmware binary becomes too large and OTA updates will fail with "ESP does not have enough space to store OTA file." MQTT is only for ESP32 and ESP32 variants (ESP32-S2, ESP32-C3, ESP32-S3, etc).
