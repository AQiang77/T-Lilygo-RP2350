#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <TouchDrvCSTXXX.hpp>
#include <TFT_eSPI.h>
#include "utilities.h"
#include "image.h"
#include "ExtensionIOXL9555.hpp"

// TFT Pin check
#if BOARD_SPI_MOSI != TFT_MOSI || \
    BOARD_SPI_SCK != TFT_SCLK ||  \
    BOARD_TFT_CS != TFT_CS ||     \
    BOARD_TFT_DC != TFT_DC      
#error "Error! Please make sure <SerialATSetup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <SerialATSetup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <SerialATSetup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <SerialATSetup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

TouchDrvCSTXXX touch;
int16_t x[5], y[5];

void touchHomeKeyCallback(void *user_data)
{
    Serial.println("Home key pressed!");
    static uint32_t checkMs = 0;
    if (millis() > checkMs)
    {
        if (extIO.digitalRead(EXPAND_TFT_BL))
        {
            extIO.digitalWrite(EXPAND_TFT_BL, LOW);
        }
        else
        {
            extIO.digitalWrite(EXPAND_TFT_BL, HIGH);
        }
    }
    checkMs = millis() + 200;
}

void setup()
{
    Serial.begin(115200);
    delay(500);

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

    // Initialize screen , The backlight Pin has been configured in TFT_eSPI(TFT_eSPI/User_Setups/SerialATSetup214_LilyGo_T_Pico2Pro.h).
    // By default, the backlight is turned on after initializing the TFT.
    extIO.digitalWrite(EXPAND_TFT_RST, LOW);
    delay(100);
    extIO.digitalWrite(EXPAND_TFT_RST, HIGH);

    extIO.digitalWrite(EXPAND_TOUCH_RST, LOW);
    delay(100);
    extIO.digitalWrite(EXPAND_TOUCH_RST, HIGH);

    extIO.digitalWrite(EXPAND_TFT_BL, LOW);
    delay(500);     //wait tft to be ready
    extIO.digitalWrite(EXPAND_TFT_BL, HIGH);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_PINK);

    // Initialize capacitive touch
    // touch.setPins(EXPAND_TOUCH_RST, EXPAND_TOUCH_IRQ);
    touch.begin(Wire, CST226SE_SLAVE_ADDRESS, BOARD_I2C_SDA, BOARD_I2C_SCL);

    // Set the screen to turn on or off after pressing the screen Home touch button
    touch.setHomeButtonCallback(touchHomeKeyCallback);
    tft.setSwapBytes(true);
    tft.pushImage(0, 0, tft.width(), tft.height(), (uint16_t *)gImage_image);

    spr.setColorDepth(8);
    spr.createSprite(tft.width(), 60);
    spr.fillSprite(TFT_LIGHTGREY);
    spr.setTextDatum(CL_DATUM);
    spr.setTextColor(TFT_BLACK, TFT_LIGHTGREY);
    spr.drawString("Powered By LilyGo ST7796 222x480 IPS TFT", 60, 10, 2);
    spr.pushSprite(0, tft.height() - 60);
}

void loop()
{
    uint8_t touched = touch.getPoint(x, y, touch.getSupportTouchPoint());
    if (touched)
    {
        String buf = "";
        for (int i = 0; i < touched; ++i)
        {
            Serial.print("X[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(x[i]);
            Serial.print(" ");
            Serial.print(" Y[");
            Serial.print(i);
            Serial.print("]:");
            Serial.print(y[i]);
            Serial.print(" ");

            buf += "[" + String(i) + "]:";
            buf += String(x[i]);
            buf += " ";
            buf += " [" + String(i) + "]:";
            buf += String(y[i]);
            buf += " ";
        }
        Serial.println();
        spr.drawString("Powered By LilyGo ST7796 222x480 IPS TFT", 60, 10, 2);
        spr.drawString(buf, 5, 30, 2);
        spr.pushSprite(0, tft.height() - 60);
        spr.fillSprite(TFT_LIGHTGREY);
    }

    delay(5);
}
