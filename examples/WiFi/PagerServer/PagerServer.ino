/*
 Pager  Server

 A simple server that echoes any incoming messages to all
 connected clients. Connect two or more telnet sessions
 to see how server.available() and server.print() works.

 created in September 2020 for WiFiEspAT library
 by Juraj Andrassy https://github.com/jandrassy

*/
#include <WiFiEspAT.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

#ifndef WIFI_SSID
#define WIFI_SSID             "Your WiFi SSID"//"Your WiFi SSID"
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD         "Your WiFi PASSWORD"//"Your WiFi PASSWORD"
#endif

const int MAX_CLIENTS = 3;
const int CLIENT_CONN_TIMEOUT = 3600; // seconds. 1 hour

#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

WiFiServerPrint server(2323);

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

    WiFi.init(SerialAT);
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

    server.begin(MAX_CLIENTS, CLIENT_CONN_TIMEOUT);

    IPAddress ip = WiFi.localIP();
    Serial.println();
    Serial.println("Connected to WiFi network.");
    Serial.print("To access the server, connect with Telnet client to ");
    Serial.print(ip);
    Serial.println(" 2323");
}

void loop()
{

    WiFiClient client = server.available(); // returns first client which has data to read or a 'false' client
    if (client) { // client is true only if it is connected and has data to read
        String s = client.readStringUntil('\n'); // read the message incoming from one of the clients
        s.trim(); // trim eventual \r
        Serial.println(s); // print the message to Serial Monitor
        client.print("echo: "); // this is only for the sending client
        server.println(s); // send the message to all connected clients
        server.flush(); // flush the buffers
    }
}
