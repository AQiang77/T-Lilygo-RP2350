/*
  Web client

 This sketch connects to a website (http://arduino.cc)
 using the WiFi module.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified in Jul 2019 for WiFiEspAT library
 by Juraj Andrassy https://github.com/jandrassy
 */

#include <WiFiEspAT.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

#ifndef WIFI_SSID
#define WIFI_SSID             "Your WiFi SSID" //"Your WiFi SSID"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD         "Your WiFi PASSWORD"//"Your WiFi PASSWORD"
#endif

const char *server = "arduino.tips";

#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;
WiFiClient client;

void setup()
{
    Serial.begin(115200);
    while (!Serial);

    /* Configure pins for communication with ESP-AT */
    SerialAT.setRX(BOARD_WIFI_RX);
    SerialAT.setTX(BOARD_WIFI_TX);
    SerialAT.begin(115200);

    Wire.setSCL(BOARD_I2C_SCL);
    Wire.setSDA(BOARD_I2C_SDA);
    Wire.begin();

    if (!extIO.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, XL9535_I2C_ADDR))
    {
        Serial.println("Failed to find XL9535 !!!");
        while (1)
            delay(1000);
    }
    Serial.println("XL9535 found !!!");
    extIO.digitalWrite(EXPAND_WIFI_EN, HIGH);
    
    if (!WiFi.init(SerialAT)) {
        while (1) {
            Serial.println("WiFi Module is not online !");
            delay(500);
        }
    }

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println();
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }


    WiFi.disconnect();     // to clear the way. not persistent
    WiFi.setPersistent();  // set the following WiFi connection as persistent
    WiFi.endAP();          // to disable default automatic start of persistent AP at startup

    Serial.print("Connect to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // waiting for connection to Wifi network set with the SetupWiFiConnection sketch
    Serial.println("Waiting for connection to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print('.');
    }
    Serial.println();
    Serial.println("Connected to WiFi network.");

    Serial.println("Starting connection to server...");
    if (client.connect(server, 80)) {
        Serial.println("connected to server");

        client.println("GET /asciilogo.txt HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();
        client.flush();
    }
}

void loop()
{

    // if there are incoming bytes available
    // from the server, read them and print them
    while (client.available()) {
        char c = client.read();
        Serial.write(c);
    }

    // if the server's disconnected, stop the client
    if (!client.connected()) {
        Serial.println();
        Serial.println("disconnecting from server.");
        client.stop();

        // do nothing forevermore
        while (true);
    }
}
