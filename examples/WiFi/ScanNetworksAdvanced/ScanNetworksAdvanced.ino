/*

  This example  prints the board's MAC address, and
  scans for available WiFi networks using a esp8266 with AT firmware.
  Every ten seconds, it scans again. It doesn't actually
  connect to any network, so no encryption scheme is specified.
  BSSID and WiFi channel are printed

  This example is based on ScanNetworks
  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 21 Junn 2012
  by Tom Igoe and Jaymes Dec

  created 1 Mar 2017
  by Arturo Guadalupi

*/

#include <WiFiEspAT.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

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

    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println();
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    // print your MAC address:
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    printMacAddress(mac);

    // scan for existing networks:
    Serial.println();
    Serial.println("Scanning available networks...");
    listNetworks();
}

void loop()
{
    delay(5000);
    // scan for existing networks:
    Serial.println("Scanning available networks...");
    listNetworks();
}

void listNetworks()
{
    // scan for nearby networks:
    Serial.println("** Scan Networks **");
    int numSsid = WiFi.scanNetworks();
    if (numSsid == -1) {
        Serial.println("Couldn't get a WiFi connection");
        while (true);
    }

    // print the list of networks seen:
    Serial.print("number of available networks: ");
    Serial.println(numSsid);

    // print the network number and name for each network found:
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
        Serial.print(thisNet + 1);
        Serial.print(") ");
        Serial.print("Signal: ");
        Serial.print(WiFi.RSSI(thisNet));
        Serial.print(" dBm");
        Serial.print("\tChannel: ");
        Serial.print(WiFi.channel(thisNet));
        byte bssid[6];
        Serial.print("\t\tBSSID: ");
        printMacAddress(WiFi.BSSID(thisNet, bssid));
        Serial.print("\tEncryption: ");
        printEncryptionType(WiFi.encryptionType(thisNet));
        Serial.print("\t\tSSID: ");
        Serial.println(WiFi.SSID(thisNet));
        Serial.flush();
    }
    Serial.println();
}

void printEncryptionType(int thisType)
{
    // read the encryption type and print out the name:
    switch (thisType) {
    case ENC_TYPE_WEP:
        Serial.print("WEP");
        break;
    case ENC_TYPE_TKIP:
        Serial.print("WPA");
        break;
    case ENC_TYPE_CCMP:
        Serial.print("WPA2");
        break;
    case ENC_TYPE_NONE:
        Serial.print("None");
        break;
    case ENC_TYPE_AUTO:
        Serial.print("Auto");
        break;
    case ENC_TYPE_UNKNOWN:
    default:
        Serial.print("Unknown");
        break;
    }
}

void print2Digits(byte thisByte)
{
    if (thisByte < 0xF) {
        Serial.print("0");
    }
    Serial.print(thisByte, HEX);
}

void printMacAddress(byte mac[])
{
    for (int i = 5; i >= 0; i--) {
        if (mac[i] < 16) {
            Serial.print("0");
        }
        Serial.print(mac[i], HEX);
        if (i > 0) {
            Serial.print(":");
        }
    }
    Serial.println();
}
