/**
 * @file      PMU_Example.ino
 * @author    LQ 
 * @license   MIT
 * @copyright Copyright (c) 2024  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2024-11-03
 * @note      USB_CDC_ON_BOOT = Disable  , Messages are output from the QWIIC serial port
 */
#include <XPowersLib.h>
#include "utilities.h"
#include "HardwareSerial.h"

PowersSY6970 PMU;

uint32_t cycleInterval;

void setup()
{
    Serial.begin(115200);

    Serial2.setRX(21);
    Serial2.setTX(20);
    Serial2.begin(115200);

    bool result = PMU.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, SY6970_SLAVE_ADDRESS);

    if (result == false) {
        while (1) {
            Serial.println("PMU is not online...");
            delay(50);
        }
    }
    // Set USB input current limit
    PMU.setInputCurrentLimit(1000);

    // Set the charging target voltage, Range:3840 ~ 4608mV ,step:16 mV
    PMU.setChargeTargetVoltage(3856);

    // Set the precharge current , Range: 64mA ~ 1024mA ,step:64mA
    PMU.setPrechargeCurr(64);

    // Set the charging current , Range:0~5056mA ,step:64mA
    PMU.setChargerConstantCurr(320);

    // To obtain voltage data, the ADC must be enabled first
    PMU.enableADCMeasure();
    PMU.enableStatLed();
    PMU.disableOTG();


    // For devices that have been connected to the battery, the charging function is turned on by default.
    // PMU.enableCharge();

    // For boards without an external battery, the charging function should be turned off, otherwise the power supply current of the power chip will be limited.
    PMU.disableCharge();
}



void loop()
{

    // SY6970 When VBUS is input, the battery voltage detection will not take effect
    if (millis() > cycleInterval) {
        Serial.print("Sats:");
        Serial.print(PMU.isVbusIn() ? "Connected" : "Disconnect"); Serial.print("\n");
        Serial.print("VBUS(mV):");
        Serial.print(PMU.getVbusVoltage()); Serial.print("\n");
        Serial.print("VBAT(mV):");
        Serial.print(PMU.getBattVoltage()); Serial.print("\n");
        Serial.print("SYS(mV):");
        Serial.print(PMU.getSystemVoltage()); Serial.print("\n");
        Serial.print("VbusStatus:");Serial.print("0x");
        Serial.print(PMU.getBusStatus()); Serial.print("\n");
        Serial.print("String:");
        Serial.print(PMU.getBusStatusString()); Serial.print("\n");
        Serial.print("ChargeStatus:");Serial.print("0x");
        Serial.print(PMU.chargeStatus()); Serial.print("\n");
        Serial.print("String:");
        Serial.print(PMU.getChargeStatusString()); Serial.print("\n");
        Serial.print("TargetVoltage(mV):");
        Serial.print(PMU.getChargeTargetVoltage()); Serial.print("\n");
        Serial.print("ChargeCurrent(mV):");
        Serial.print(PMU.getChargerConstantCurr()); Serial.print("\n");
        Serial.print("Precharge(mV):");
        Serial.print(PMU.getPrechargeCurr()); Serial.print("\n");        
        Serial.print("NTCStatus:");
        Serial.print(PMU.getNTCStatus()); Serial.print("\n");        
        Serial.print("String:");
        Serial.print(PMU.getNTCStatusString()); Serial.print("\n");        
        Serial.println();

        Serial2.println("Sats:");
        Serial2.print(PMU.isVbusIn() ? "Connected" : "Disconnect"); Serial2.print("\n");
        Serial2.print("VBUS(mV):");
        Serial2.print(PMU.getVbusVoltage()); Serial2.print("\n");
        Serial2.print("VBAT(mV):");
        Serial2.print(PMU.getBattVoltage()); Serial2.print("\n");
        Serial2.print("SYS(mV):");
        Serial2.print(PMU.getSystemVoltage()); Serial2.print("\n");
        Serial2.print("VbusStatus:");Serial2.print("0x");
        Serial2.print(PMU.getBusStatus()); Serial2.print("\n");
        Serial2.print("String:");
        Serial2.print(PMU.getBusStatusString()); Serial2.print("\n");
        Serial2.print("ChargeStatus:");Serial2.print("0x");
        Serial2.print(PMU.chargeStatus()); Serial2.print("\n");
        Serial2.print("String:");
        Serial2.print(PMU.getChargeStatusString()); Serial2.print("\n");
        Serial2.print("TargetVoltage(mV):");
        Serial2.print(PMU.getChargeTargetVoltage()); Serial2.print("\n");
        Serial2.print("ChargeCurrent(mV):");
        Serial2.print(PMU.getChargerConstantCurr()); Serial2.print("\n");
        Serial2.print("Precharge(mV):");
        Serial2.print(PMU.getPrechargeCurr()); Serial2.print("\n");        
        Serial2.print("NTCStatus:");
        Serial2.print(PMU.getNTCStatus()); Serial2.print("\n");        
        Serial2.print("String:");
        Serial2.print(PMU.getNTCStatusString()); Serial2.print("\n");        
        Serial2.println();

        cycleInterval = millis() + 2000;
    }

}





