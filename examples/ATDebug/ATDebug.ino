
#include <Arduino.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

// AT Command Set:
// ESP32-C3: https://docs.espressif.com/projects/esp-at/en/latest/esp32c3/Get_Started/index.html
#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

void test_AT()
{
    SerialAT.print("AT\r\n");
    String input = SerialAT.readString();
    Serial.println(input);
}

void setup()
{
    Serial.begin(115200);
    // Ensure the UART pinout the WiFi Module is connected to is configured properly
    while (!Serial);
    Serial.println("Open Serial");

    SerialAT.setTX(BOARD_WIFI_TX);
    SerialAT.setRX(BOARD_WIFI_RX);
    SerialAT.begin(115200);  
   
    delay(100);
    test_AT();
}

void loop()
{
    while (SerialAT.available()) {
        Serial.write(SerialAT.read());
    }
    while (Serial.available()) {
        SerialAT.write(Serial.read());
    }
    delay(5);
}

