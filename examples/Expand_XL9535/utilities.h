/**
 * @file      utilities.h
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2023-10-11
 *
 */
#pragma once
// https://www.lilygo.cc/products/t-pico-pro
// T-Pico-Pro pinmap

#define NOT_USE             (-1)

// LTR553 , TOUCH , SY6970 share I2C Bus
#define BOARD_I2C_SDA       0
#define BOARD_I2C_SCL       1

// Not use
#define QWIIC_I2C_SDA       2
#define QWIIC_I2C_SCL       3

#define QWIIC_UART_RX       21
#define QWIIC_UART_TX       30

//expand

#define EXPAND_GPIO0        0
#define EXPAND_GPIO1        1
#define EXPAND_GPIO2        2
#define EXPAND_GPIO3        3
#define EXPAND_GPIO4        4
#define EXPAND_GPIO5        5
#define EXPAND_GPIO6        6

// WIFI Module
#define BOARD_WIFI_RX       29
#define BOARD_WIFI_TX       28
#define BOARD_WIFI_CTS      26
#define BOARD_WIFI_RTS      27
#define BOARD_WIFI_EN       EXPAND_GPIO3
#define BOARD_WIFI_IRQ      22


// SD , TFT share SPI Bus
#define BOARD_SPI_MISO      4
#define BOARD_SPI_MOSI      7
#define BOARD_SPI_SCK       6
#define BOARD_TFT_CS        8
#define BOARD_TFT_DC        9
#define BOARD_TFT_RST       EXPAND_GPIO0
#define BOARD_TFT_BL        EXPAND_GPIO1
#define BOARD_SD_CS         5

#define BOARD_SENSOR_IRQ    19
#define BOARD_TOUCH_RST     EXPAND_GPIO2
#define BOARD_TOUCH_IRQ     EXPAND_GPIO4
#define BOARD_TFT_WIDTH     222
#define BOARD_TFT_HEIHT     480

// BUTTON Pinmap
#define BOARD_USER_BUTTON   {23 /*btn1*/,24/*btn2*/}
#define BOARD_USER_BTN_NUM  2

#define SerialAT        Serial1
