#include <Arduino.h>
#include <TFT_eSPI.h>
#include "image.h"
#include "utilities.h"
#include "ExtensionIOXL9555.hpp"

#if (BOARD_SPI_MISO != TFT_MISO) || (BOARD_SPI_MOSI != TFT_MOSI) || \
    (BOARD_SPI_SCK != TFT_SCLK) || (TFT_CS != BOARD_TFT_CS) || \
    (TFT_DC != BOARD_TFT_DC) 
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

TFT_eSPI tft = TFT_eSPI();
#define XL9535_I2C_ADDR 0x24
ExtensionIOXL9555 extIO;

// 16 levels of adjustment range
// The adjustable range is 0~15, 0 is the minimum brightness, 15 is the maximum brightness
void setBrightness(uint8_t value)
{
    Serial.println("setBrightness");
    static uint8_t level = 0;
    static uint8_t steps = 16;
    if (value == 0)
    {
        extIO.digitalWrite(EXPAND_TFT_BL, LOW);
        delay(3);
        level = 0;
        return;
    }
    if (level == 0)
    {
        extIO.digitalWrite(EXPAND_TFT_BL, HIGH);
        level = steps;
        delayMicroseconds(30);
    }
    int from = steps - level; //current brightness
    int to = steps - value;   //goal brightness
    int num = (steps + to - from) % steps; // number of steps 
    for (int i = 0; i < num; i++)
    {
        extIO.digitalWrite(EXPAND_TFT_BL, LOW);
        extIO.digitalWrite(EXPAND_TFT_BL, HIGH);
    }
    level = value;
}

void setup()
{
    Serial.begin(115200);

    Wire.setSCL(BOARD_I2C_SCL);
    Wire.setSDA(BOARD_I2C_SDA);
    Wire.begin();

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
    // // // Set PORT1 as output ,mask = 0x00 = all pin output
    extIO.configPort(ExtensionIOXL9555::PORT1, 0x00);
    delay(100);

    extIO.digitalWrite(EXPAND_TFT_RST, LOW);
    delay(100);
    extIO.digitalWrite(EXPAND_TFT_RST, HIGH);

    extIO.digitalWrite(EXPAND_TFT_BL, LOW);
    delay(500);     //wait tft to be ready
    extIO.digitalWrite(EXPAND_TFT_BL, HIGH);

    tft.begin();
    tft.setRotation(1);
    tft.setSwapBytes(true);

    tft.fillScreen(TFT_RED);
    delay(300);
    tft.fillScreen(TFT_GREEN);
    delay(300);
    tft.fillScreen(TFT_BLUE);
    delay(300);
}

void loop()
{
    Serial.println("TFT_TEST");

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString("Test", 0, 0, 4);
    tft.drawString("1234567890", 0, 40, 2);
    tft.drawString("1234567890", 0, 80, 4);
    delay(5000);

    tft.pushImage(0, 0, tft.width(), tft.height(), (uint16_t *)gImage_image);

    // adjus tft brightness , 16 level
    for (int i = 0; i < 16; ++i)
    {
        setBrightness(i);
        delay(200);
    }

    delay(5000);
}
