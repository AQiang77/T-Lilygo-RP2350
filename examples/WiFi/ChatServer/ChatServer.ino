/*
 Chat  Server

 A simple server that echoes any incoming messages to a
 connected client. To use telnet to your device's IP address and type.
 You can see the client's input in the serial monitor as well.

 created 18 Dec 2009
 by David A. Mellis
 modified 31 May 2012
 by Tom Igoe

 modified in Jul 2019 for WiFiEspAT library
 by Juraj Andrassy https://github.com/jandrassy

*/
#include "WiFiEspAT.h"
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"
#include <Wire.h>

#ifndef WIFI_SSID
#define WIFI_SSID "67Q"//"xinyuandianzi_AX"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "67676767"//"AA15994823428"
#endif

#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

WiFiServer server(2323);
WiFiClient client;

void setup()
{
    Serial.begin(115200);
    // while (!Serial);
    delay(1000);

    /* Configure pins for communication with ESP-AT */
    SerialAT.setRX(BOARD_WIFI_RX);
    SerialAT.setTX(BOARD_WIFI_TX);
    SerialAT.begin(115200);

    Wire.setSCL(BOARD_I2C_SCL);
    Wire.setSDA(BOARD_I2C_SDA);
    Wire.begin();

    while (!extIO.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, XL9535_I2C_ADDR))
    {
        Serial.println("Failed to find XL9535 !!!");
        delay(1000);
    }
    Serial.println("XL9535 found !!!");
    extIO.digitalWrite(EXPAND_WIFI_EN, HIGH);

    WiFi.init(SerialAT, BOARD_WIFI_EN);

    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println();
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    WiFi.disconnect();    // to clear the way. not persistent
    WiFi.setPersistent(); // set the following WiFi connection as persistent
    WiFi.endAP();         // to disable default automatic start of persistent AP at startup

    Serial.print("Connect to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // waiting for connection to Wifi network set with the SetupWiFiConnection sketch
    Serial.println("Waiting for connection to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print('.');
    }
    Serial.println();

    server.begin();

    IPAddress ip = WiFi.localIP();
    Serial.println();
    Serial.println("Connected to WiFi network.");
    Serial.print("To access the server, connect with Telnet client to ");
    Serial.print(ip);
    Serial.println(" 2323\".");
}

void loop()
{
    if (!client)
    {
        client = server.available();
        if (client)
        {
            Serial.println("We have a new client");
            client.println("Hello, client!");
            client.flush();
        }
    }

    if (client)
    {
        while (client.available() > 0)
        {
            // read the bytes incoming from the client:
            char thisChar = client.read();
            // echo the bytes back to the client:
            client.write(thisChar);
            // echo the bytes to the server as well:
            Serial.write(thisChar);
        }
        client.flush();
        if (!client.connected())
        {
            Serial.println("Client disconnected.");
        }
    }
}
