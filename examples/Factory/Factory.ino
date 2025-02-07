/**
 * @file      Factory_test.ino
 * @author    LQ
 * @license   MIT
 * @copyright Copyright (c) 2024  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2024-11-10
 * @note      USB_CDC_ON_BOOT = Disable  , Messages are output from the QWIIC serial port
 */

#include <Arduino.h>
#include "WiFiEspAT.h"
#include <SPI.h>
#include "utilities.h"
#include <TFT_eSPI.h>
#include "ExtensionIOXL9555.hpp"
#include "AceButton.h"
#include <TouchDrvCSTXXX.hpp>
#include <Wire.h>
#include <SD.h>
#include <XPowersLib.h>
#include <lvgl.h> // https://github.com/lvgl/lvgl
#include "gui.h"
#include "event_init.h"
#include <TaskScheduler.h>
// #include "hardware/adc.h"

using namespace ace_button;

#define XL9535_I2C_ADDR 0x24
#define Default_WiFi_SSID "xinyuandianzi"
#define Default_WiFi_PASSWORD "AA15994823428"

#if (BOARD_SPI_MISO != TFT_MISO) || (BOARD_SPI_MOSI != TFT_MOSI) || \
    (BOARD_SPI_SCK != TFT_SCLK) || (TFT_CS != BOARD_TFT_CS) ||      \
    (TFT_DC != BOARD_TFT_DC)
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#error "Error! Please make sure <Setup212_LilyGo_T_PicoPro.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

/*************************/
// Variable declaration
/*************************/
static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
static lv_disp_drv_t disp_drv;      // contains callback functions
static lv_disp_draw_buf_t draw_buf;
#define LV_BUFFER_SIZE TFT_HEIGHT *TFT_WIDTH / 2
#ifdef USING_MALLOC_FUNC
static lv_color_t *lv_disp_buf;
#else
static lv_color_t lv_disp_buf[LV_BUFFER_SIZE];
#endif

const uint8_t btns[BOARD_USER_BTN_NUM] = BOARD_USER_BUTTON;
String wifi_ssid_buf;

bool Expand_status, PMU_status, Touch_status, SD_status, WiFi_status, Screen_status;
static bool isBacklightOn = true;
static bool manualOff = false;
bool WiFi_connect_status = false;
bool wifi_connect = false;
bool bettary_enable = false;

String wifi_ssid = Default_WiFi_SSID;
String wifi_password = Default_WiFi_PASSWORD;
const int time_zone = 8;
const char *server1 = "ntp.sjtu.edu.cn";
const char *server2 = "cn.ntp.org.cn";

uint16_t max_voltage = 3856;
uint16_t min_voltage = 0;
uint16_t voltage_step_size = 38;
uint8_t percentage_voltage = 0;

/*************************/
// Object declaration
/*************************/
ExtensionIOXL9555 extIO;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
TouchDrvCSTXXX touch;
int16_t x[5], y[5];
File root;
PowersSY6970 PMU;
lv_ui ui;
IPAddress ip;
WiFiServer server(2323);
WiFiClient client;
WiFiClass WiFi_AT;
AceButton btn1(/*PIN*/ btns[0], /*DEFAULT STATE*/ HIGH, /*ID*/ 0);

void t1Callback();
void t2Callback();
static void button_handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState);
String macAddress(void);
String get_WIFI_SSID(void);
void WiFi_connect();
void setBrightness(uint8_t value);
void PMU_set();
void printDirectory(File dir, int numTabs);
void Module_init();
void touchHomeKeyCallback(void *user_data);
static void lvgl_flush_callback(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);
static void lv_touchpad_read_callback(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
bool esp_sleep_set(uint8_t wakeup_source, uint8_t pin, uint8_t mode);
bool esp_ntp_set(uint8_t enable, uint8_t timezone, const char *server1, const char *server2);
bool esp_get_ntp_time();

Task t1(1000, TASK_FOREVER, &t1Callback);
Task t2(1, TASK_FOREVER, &t2Callback);
Scheduler runner;

void setup()
{
    Serial.begin(115200);

    // uint32_t freq = clock_get_hz(clk_sys);
    // Serial.printf("CPU Freq: %lu MHz\n", freq / 1000 / 1000);
    // Serial.printf("PSRAM Size: %d\r\n", rp2040.getPSRAMSize());

    Module_init();

    lv_init();
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf, NULL, LV_BUFFER_SIZE);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = tft.width();
    disp_drv.ver_res = tft.height();
    disp_drv.flush_cb = lvgl_flush_callback;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register touch brush with LVGL */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lv_touchpad_read_callback;
    lv_indev_drv_register(&indev_drv);

    time_info.tm_year = 2024;
    time_info.tm_mon = 0;
    time_info.tm_mday = 1;
    time_info.tm_hour = 0;
    time_info.tm_min = 0;
    time_info.tm_sec = 0;

    strcpy(week, "Mon");
    strcpy(str_mon, "Jan");

    runner.init();

    runner.addTask(t1);
    runner.addTask(t2);
    delay(500);
    t1.enable();
    t2.enable();

    if (WiFi_status)
    {
        int thisNet, numssid;
        numssid = WiFi_AT.scanNetworks();
        if (numssid > 0)
        {
            for (thisNet = 0; thisNet < numssid; thisNet++)
            {
                wifi_ssid_buf += WiFi_AT.SSID(thisNet);
                wifi_ssid_buf += "\n";
            }
            Serial.println(wifi_ssid_buf);
            if (wifi_ssid_buf.indexOf(Default_WiFi_SSID) != -1)
            {
                wifi_connect = true;
            }
        }
        else
        {
            Serial.println("No SSID found");
        }

        pinMode(BOARD_WIFI_AT_WAKEUP, OUTPUT);
        digitalWrite(BOARD_WIFI_AT_WAKEUP, HIGH);
        if (esp_sleep_set(2, BOARD_WIFI_AT_WAKEUP, 0)) // wakeup_source = 2,GPIO wakeup resoure: io22 LOW
        {
            Serial.println("esp_sleep_set success");
        }
        else
        {
            Serial.println("esp_sleep_set fail");
        }
        WiFi_AT.sleepMode(WIFI_LIGHT_SLEEP);
    }

    if (Touch_status)
    {
        Check_Moudle_gui(&ui);
        gui_Main_interface(&ui);
        gui_Set_interface(&ui);
        WIFI_input_gui(&ui);

        delay(50);
        lv_scr_load(ui.screen);
    }
}

void loop()
{
    runner.execute();
}

bool esp_sleep_set(uint8_t wakeup_source, uint8_t pin, uint8_t mode) // wakeup_source = 2：GPIO 唤醒
{
    // Serial.println("esp_sleep_set");
    char buffer[64] = {0};
    snprintf(buffer, 64, "AT+SLEEPWKCFG=%d,%d,%d\r\n", wakeup_source, pin, mode);
    SerialAT.write(buffer);
    String response = SerialAT.readString();
    if (response.indexOf("OK") >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool esp_ntp_set(uint8_t enable, uint8_t timezone, const char *server1, const char *server2)
{
    Serial.println("esp_ntp_set");
    char buffer[128] = {0};
    snprintf(buffer, 128, "AT+CIPSNTPCFG=%d,%d,\"%s\",\"%s\"\r\n", enable, timezone, server1, server2);
    SerialAT.write(buffer);
    String response = SerialAT.readString();
    if (response.indexOf("OK") >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool esp_get_ntp_time()
{
    Serial.println("esp_get_ntp_time");
    String response;
    char buffer[64] = {0};
    snprintf(buffer, 64, "AT+CIPSNTPTIME?\r\n");
    SerialAT.write(buffer);

    unsigned long startTime = millis();
    while (millis() - startTime < 1000)
    { // 1秒超时
        if (SerialAT.available())
        {
            response += (char)SerialAT.read();
        }
    }
    // Serial.println(response);

    if (response.indexOf("OK") >= 0)
    {
        if (response.indexOf("+CIPSNTPTIME:") >= 0 && !(response.indexOf("1970") >= 0))
        {
            int startIndex = response.indexOf("+CIPSNTPTIME:") + 13;
            int endIndex = response.indexOf("\r\n", startIndex);
            String timeStr = response.substring(startIndex, endIndex);
            // Serial.printf("timeStr:%s\n", timeStr.c_str());
            sscanf(timeStr.c_str(), "%3s %3s %d %d:%d:%d %d", week, str_mon, &time_info.tm_mday, &time_info.tm_hour, &time_info.tm_min,
                   &time_info.tm_sec, &time_info.tm_year);
            Serial.printf("time:%d,%d,%d,%d,%d,%d\n", time_info.tm_year, time_info.tm_mon, time_info.tm_mday, time_info.tm_hour,
                          time_info.tm_min, time_info.tm_sec);
            Serial.println(String(week) + String(str_mon));
        }
        else
        {
            Serial.println("get time error!");
            return false;
        }
    }
    return true;
}

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

static void lvgl_flush_callback(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    // Serial.println("flush callback");
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, false);
    tft.endWrite();
    lv_disp_flush_ready(drv);
}

static void lv_touchpad_read_callback(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    int16_t x[5], y[5];
    if (touch.getPoint(x, y, 1))
    {
        // Serial.println("touch callback");
        data->point.x = x[0];
        data->point.y = y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    delay(10);
}

void t1Callback()
{
    uint8_t static time = 0;
    // Serial.printf("t1 time:%d\n",time);
    if (wifi_connect == true && WiFi_status)
    {
        // WiFi_AT.sleepMode(WIFI_NONE_SLEEP);
        pinMode(BOARD_WIFI_AT_WAKEUP, OUTPUT);
        digitalWrite(BOARD_WIFI_AT_WAKEUP, LOW);
        delay(100);
        if (WiFi_AT.status() != WL_CONNECTED)
        {
            WiFi_AT.disconnect(); // to clear the way. not persistent
            WiFi_connect_status = false;
            wifi_connect = false;
            Serial.println("Connection to WiFi failed.");
            lv_obj_del(ui.screen_wifi_lable_wait_connect);

            WiFi_connect();
            Serial.print("To access the server, connect with Telnet client to ");
            Serial.print(ip);
            Serial.println(" 2323\".");
            if (esp_ntp_set(1, time_zone, server1, server2))
            {
                Serial.println("NTP set success");
            }
        }

        if (WiFi_AT.status() == WL_CONNECTED)
        {
            wifi_connect = false;
            WiFi_connect_status = true;

            ip = WiFi_AT.localIP();
            Serial.println("Connected to WiFi network.");

            Serial.print("FW Version:");
            Serial.println(WiFi_AT.firmwareVersion());
            Serial.println("MAC: " + macAddress());


            lv_obj_del(ui.screen_wifi_lable_wait_connect);

            delay(50);

            if (esp_get_ntp_time())
            {
                Serial.println("NTP get success");
            }
            else
            {
                wifi_connect = true;
            }
        }
    }
}

void t2Callback()
{
    lv_task_handler();
    btn1.check();
    delay(5);
}

// The event handler for the button.
static void button_handleEvent(AceButton *button, uint8_t eventType, uint8_t buttonState)
{
    // Print out a message for all events.
    Serial.print(F("handleEvent(): eventType: "));
    Serial.print(AceButton::eventName(eventType));
    Serial.print(F("; buttonState: "));
    Serial.println(buttonState);
    uint8_t id = button->getId();
    uint8_t r = tft.getRotation();
    switch (eventType)
    {
    case AceButton::kEventPressed:
        Serial.printf("ID:%d is Pressed!", id);
        if (r == 3)
        {
            tft.setRotation(1);
            lv_disp_drv_update(lv_disp_get_default(), &disp_drv);
            touch.setMirrorXY(false, true);
        }
        else if (r == 1)
        {
            tft.setRotation(3);
            lv_disp_drv_update(lv_disp_get_default(), &disp_drv);
            touch.setMirrorXY(true, false);
        }
        break;
    default:
        break;
    }
}

void PMU_set()
{
    // Set USB input current limit
    PMU.setInputCurrentLimit(1000);
    // Set the charging target voltage, Range:3840 ~ 4608mV ,step:16 mV
    PMU.setChargeTargetVoltage(3840);
    // Set the precharge current , Range: 64mA ~ 1024mA ,step:64mA
    PMU.setPrechargeCurr(192);
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

    max_voltage = PMU.getChargeTargetVoltage(); // read max vlotage
    voltage_step_size = max_voltage / 100;      // step size
    percentage_voltage = PMU.getBattVoltage() / voltage_step_size;
    if (percentage_voltage > 100)
    {
        percentage_voltage = 100;
    }
}

void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            Serial.println("no more files!"); // no more files
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory())
        {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            // files have sizes, directories do not
            Serial.print("\t\t");
            Serial.print(entry.size(), DEC);
            time_t cr = entry.getCreationTime();
            time_t lw = entry.getLastWrite();
            struct tm *tmstruct = localtime(&cr);
            Serial.printf("\tCREATION: %d-%02d-%02d %02d:%02d:%02d", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
            tmstruct = localtime(&lw);
            Serial.printf("\tLAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
        }
        entry.close();
    }
}

void Module_init()
{
    // Serial.println("Module init...");
    SPI.setRX(BOARD_SPI_MISO);
    SPI.setTX(BOARD_SPI_MOSI);
    SPI.setSCK(BOARD_SPI_SCK);

    // Share SPI Bus , disable bus spi devices
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
    pinMode(BOARD_SD_CS, OUTPUT);
    digitalWrite(BOARD_SD_CS, HIGH);

    Wire.setSCL(BOARD_I2C_SCL);
    Wire.setSDA(BOARD_I2C_SDA);
    Wire.begin();
    delay(50);

    pinMode(btns[0], INPUT_PULLUP);
    btn1.init(btns[0], HIGH, 0);
    ButtonConfig *buttonConfig = ButtonConfig::getSystemButtonConfig();
    buttonConfig->setEventHandler(button_handleEvent);
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);

    /***************************/
    // Initialize the Expand module
    /***************************/
    Expand_status = extIO.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, XL9535_I2C_ADDR);
    if (!Expand_status)
    {
        Serial.println("Failed to find XL9535 !!!");
    }
    else
    {
        Serial.println("XL9535 found !!!");
    }

    extIO.configPort(ExtensionIOXL9555::PORT0, 0x00);
    delay(50);

    /***************************/
    // Initialize the SY6970 module
    /***************************/
    PMU_status = PMU.init(Wire, BOARD_I2C_SDA, BOARD_I2C_SCL, SY6970_SLAVE_ADDRESS);
    if (!PMU_status)
    {
        Serial.println("PMU is not online...");
        delay(50);
    }
    else
    {
        Serial.println("PMU found !!!");
        PMU_set();
    }

    /***************************/
    // Initialize the SD Card
    /***************************/
    SD_status = SD.begin(BOARD_SD_CS);
    if (!SD_status)
    {
        Serial.println("Card failed, or not present");
    }
    else
    {
        Serial.print("SD initialization done.");
        Serial.print(SD.size64() / 1024 / 1024.0);
        Serial.println("MB");
    }
    // root = SD.open("/");
    // printDirectory(root, 0);
    // root.close();

    /***************************/
    // Initialize the TFT Srceen
    /***************************/
    extIO.digitalWrite(EXPAND_TFT_RST, LOW);
    delay(50);
    extIO.digitalWrite(EXPAND_TFT_RST, HIGH);

    extIO.digitalWrite(EXPAND_TFT_BL, LOW);
    delay(500); // wait tft to be ready
    extIO.digitalWrite(EXPAND_TFT_BL, HIGH);

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    delay(50);

    /***************************/
    // Initialize the touch Srceen
    /***************************/
    extIO.digitalWrite(EXPAND_TOUCH_RST, LOW);
    delay(50);
    extIO.digitalWrite(EXPAND_TOUCH_RST, HIGH);

    touch.setPins(EXPAND_TOUCH_RST, EXPAND_TOUCH_IRQ);
    Touch_status = touch.begin(Wire, CST226SE_SLAVE_ADDRESS, BOARD_I2C_SDA, BOARD_I2C_SCL);
    if (!Touch_status)
    {
        Serial.println("Touch is not online...");
        delay(50);
    }
    else
    {
        Serial.println("Touch found !!!");
        // Set the screen to turn on or off after pressing the screen Home touch button
        touch.setMaxCoordinates(tft.width(), tft.height());
        touch.setSwapXY(true);
        touch.setMirrorXY(true, false);
        touch.setHomeButtonCallback([](void *user_data)
                                    {
            Serial.println("Home key pressed!");
            static uint32_t checkMs = 0;
            if (millis() > checkMs) {
                if (isBacklightOn) {  
                    setBrightness(0);
                    Serial.println("turn off!");

                    manualOff = true;
                    isBacklightOn = false;
                } else { 
                    manualOff = false;
                    isBacklightOn = true;
                    setBrightness(16);
                    Serial.println("turn on!");
                }
            }
            checkMs = millis() + 200; }, NULL);
    }

    /***************************/
    // Initialize the WiFi module
    /***************************/
    SerialAT.setRX(BOARD_WIFI_RX);
    SerialAT.setTX(BOARD_WIFI_TX);
    SerialAT.begin(115200);
    extIO.digitalWrite(EXPAND_WIFI_EN, HIGH);
    WiFi_status = WiFi_AT.init(SerialAT);

    if (!WiFi_status)
    {
        Serial.println("WiFi Module is not online !");
    }

    if (WiFi_status)
    {
        Serial.println("WiFi Module found !");
        WiFi_AT.disconnect();    // to clear the way. not persistent
        WiFi_AT.setPersistent(); // set the following WiFi_AT connection as persistent
        WiFi_AT.endAP();         // to disable default automatic start of persistent AP at startup
        WiFi_AT.setAutoConnect(false);
    }
}

void setBrightness(uint8_t value)
{
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
    int from = steps - level;
    int to = steps - value;
    int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++)
    {
        extIO.digitalWrite(EXPAND_TFT_BL, LOW);
        extIO.digitalWrite(EXPAND_TFT_BL, HIGH);
    }
    level = value;
}

void WiFi_connect()
{
    Serial.println("WiFi connecting...");
    WiFi_AT.setPersistent(); // set the following WiFi_AT connection as persistent
    WiFi_AT.endAP();         // to disable default automatic start of persistent AP at startup
    WiFi_AT.begin(wifi_ssid.c_str(), wifi_password.c_str());
    server.begin();
}

String macAddress(void)
{
    uint8_t mac[6];
    char macStr[18] = {0};
    WiFi_AT.macAddress(mac);
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(macStr);
}

String get_WIFI_SSID(void)
{
    return String(wifi_ssid);
}