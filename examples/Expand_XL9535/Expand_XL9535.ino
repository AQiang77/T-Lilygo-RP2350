#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

ExtensionIOXL9555 extIO;
#define XL9535_I2C_ADDR 0x24

void setup(){
    Serial.begin(115200);

    Wire.setSCL(BOARD_I2C_SCL);
    Wire.setSDA(BOARD_I2C_SDA);
    Wire.begin();

    delay(300);
    if (!extIO.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, XL9535_I2C_ADDR))
    {
        Serial.println("Failed to find Expand XL9535 !!!");
        while (1)
            delay(1000);
    }
    Serial.println("Expand XL9535 found !!!");
    // Set PORT0 as output ,mask = 0x00 = all pin output
    extIO.configPort(ExtensionIOXL9555::PORT0, 0x00);
    delay(100);
    // Set PORT1 as output ,mask = 0x00 = all pin output
    extIO.configPort(ExtensionIOXL9555::PORT1, 0x00);
    delay(100);
    // Set IO6 as input,mask = 0xFF = all pin input
    extIO.configPort(ExtensionIOXL9555::IO6, 0xFF);
}

void loop(){
    Serial.println("Toggle LED LOW");
    extIO.digitalWrite(ExtensionIOXL9555::IO1, LOW);
    delay(1000);
    Serial.println("Toggle LED HIGH");
    extIO.digitalWrite(ExtensionIOXL9555::IO1, HIGH);
    delay(1000);
    Serial.printf("ExtensionIOXL9555::IO6:%d\n",extIO.digitalRead(ExtensionIOXL9555::IO6));
    delay(1000);
}