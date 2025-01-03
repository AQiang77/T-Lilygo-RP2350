/**
 * @file      AdjustBacklight.ino
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-11-01
 *
 */
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

// TFT Pin check
#if BOARD_SPI_MOSI != TFT_MOSI ||   \
    BOARD_SPI_SCK != TFT_SCLK ||    \
    BOARD_TFT_CS != TFT_CS ||       \
    BOARD_TFT_DC != TFT_DC ||       \
    BOARD_TFT_RST != TFT_RST ||     \
    TFT_WIDTH != BOARD_TFT_WIDTH || \
    TFT_HEIGHT != BOARD_TFT_HEIHT
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

#define BRIGHTNESS_MAX_LEVEL 16
#define XL9535_I2C_ADDR 0x24

ExtensionIOXL9555 extIO;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

void setBrightness(uint8_t value)
{
    static uint8_t level = 0;
    static uint8_t steps = 16;
    if (value == 0)
    {
        extIO.digitalWrite(BOARD_TFT_BL, LOW);
        delay(3);
        level = 0;
        return;
    }
    if (level == 0)
    {
        extIO.digitalWrite(BOARD_TFT_BL, HIGH);
        level = steps;
        delayMicroseconds(30);
    }
    int from = steps - level;
    int to = steps - value;
    int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++)
    {
        extIO.digitalWrite(BOARD_TFT_BL, LOW);
        extIO.digitalWrite(BOARD_TFT_BL, HIGH);
    }
    level = value;
}

void setup()
{
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

    extIO.digitalWrite(BOARD_TFT_RST, LOW);
    delay(10);
    extIO.digitalWrite(BOARD_TFT_BL, HIGH);
    delay(10);
    extIO.digitalWrite(BOARD_TFT_RST, HIGH);

    // Initialize screen , The backlight Pin has been configured in TFT_eSPI(TFT_eSPI/User_Setups/Setup212_LilyGo_T_PicoPro.h).
    // By default, the backlight is turned on after initializing the TFT.
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    spr.setColorDepth(8);
    spr.createSprite(tft.width(), 60);
    spr.fillSprite(TFT_LIGHTGREY);
    spr.setTextDatum(CL_DATUM);
    spr.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
    spr.pushSprite(0, tft.height() / 2 - 30);
}

void loop()
{
    for (int i = BRIGHTNESS_MAX_LEVEL; i >= 0; --i)
    {
        setBrightness(i);
        String buf = "Set brightness : " + String(i);
        spr.drawString(buf, 5, 30, 2);
        spr.pushSprite(0, tft.height() / 2 - 30);
        spr.fillSprite(TFT_BLACK);
        delay(10);
    }
    delay(1000);
    for (int i = 0; i <= BRIGHTNESS_MAX_LEVEL; ++i)
    {
        setBrightness(i);
        String buf = "Set brightness : " + String(i);
        spr.drawString(buf, 5, 30, 2);
        spr.pushSprite(0, tft.height() / 2 - 30);
        spr.fillSprite(TFT_BLACK);
        delay(10);
    }
    delay(2000);
}
