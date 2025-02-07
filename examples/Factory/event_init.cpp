/*
 * Copyright 2024 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
#include <Arduino.h>
#include "event_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "gui.h"
#include "WiFi.h"

extern lv_ui ui;
extern bool bettary_enable;
extern String wifi_ssid;
extern String wifi_password;
extern bool wifi_connect;

static void screen_imgbtn_set_event_handler(lv_event_t *e);
void screen_sw_Battery_event_handler(lv_event_t *e);
void screen_btn_cancel_event_handler(lv_event_t *e);
void screen_btn_select_event_handler(lv_event_t *e);
void screen_imgbtn_back_event_handler(lv_event_t *e);
void screen_sw_batteryenable_event_handler(lv_event_t *e);
static void ta_event_cb(lv_event_t *e);
void screen_ddlist_wifi_event_handler(lv_event_t *e);

static void screen_imgbtn_set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // Serial.printf("screen_imgbtn_1_event_handler: %d\n",code);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        Serial.println("clicked");
        lv_scr_load(ui.screen_set);
        break;
    }
    default:
        break;
    }
}

void screen_sw_Battery_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // Serial.printf("screen_imgbtn_1_event_handler: %d\n",code);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        Serial.println("screen_sw_Battery_event_handler");
        break;
    }
    default:
        break;
    }
}

void screen_imgbtn_back_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // Serial.printf("screen_imgbtn_1_event_handler: %d\n",code);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        Serial.println("back");
        lv_scr_load(ui.screen);
        break;
    }
    default:
        break;
    }
}

void screen_sw_batteryenable_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        bettary_enable = !bettary_enable;
        // Serial.printf("bettary_enable: %d\n",bettary_enable);
        break;

    default:
        break;
    }
}

static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED)
    {
        Serial.println("Focused");
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if (code == LV_EVENT_DEFOCUSED)
    {
        Serial.println("DE Focused");
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

void screen_ddlist_wifi_event_handler(lv_event_t *e)
{
    char buf[64];
    int selected_index = 0,thisNet,numssid;
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_VALUE_CHANGED:
        Serial.println("ddlist wifi VALUE_CHANGED!");
        selected_index = lv_dropdown_get_selected(ui.screen_set_ddlist_wifi_ssid);
        lv_dropdown_get_selected_str(ui.screen_set_ddlist_wifi_ssid, buf, sizeof(buf)); /* 获取选中的文本 */
        wifi_ssid = String(buf);
        Serial.println("wifi_ssid:" + wifi_ssid);
        lv_scr_load(ui.screen_wifi);
        break;
    default:
        break;
    }
}

// void screen_btn_sd_event_handler(lv_event_t *e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     switch (code)
//     {
//     case LV_EVENT_CLICKED:
//         Serial.println("btn_sd clicked !");
//         break;
//     default:
//         break;
//     }
// }

void screen_btn_cancel_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
        Serial.println("cancel");
        lv_scr_load(ui.screen_set);
        break;
    default:
        break;
    }
}

void screen_btn_select_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    // String password;
    switch (code)
    {
    case LV_EVENT_CLICKED:
        Serial.println("select");
        wifi_password = lv_textarea_get_text(ui.screen_wifi_ta_wifi_password); // 获取文本框内容
        Serial.println("password:" + wifi_password);
        wifi_connect = true;
        lv_scr_load(ui.screen_set);
        ui.screen_wifi_lable_wait_connect = lv_label_create(ui.screen_set);
        lv_label_set_text(ui.screen_wifi_lable_wait_connect, "wait wifi connect...");
        lv_obj_set_size(ui.screen_wifi_lable_wait_connect, 300, 26);
        lv_obj_set_pos(ui.screen_wifi_lable_wait_connect, 90, 86);
        lv_obj_set_style_text_align(ui.screen_wifi_lable_wait_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
        lv_obj_set_style_text_color(ui.screen_wifi_lable_wait_connect, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_text_font(ui.screen_wifi_lable_wait_connect, &lv_font_Acme_Regular_24, LV_PART_MAIN);
        lv_obj_set_style_border_width(ui.screen_wifi_lable_wait_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui.screen_wifi_lable_wait_connect, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui.screen_wifi_lable_wait_connect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui.screen_wifi_lable_wait_connect, 183, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui.screen_wifi_lable_wait_connect, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);

        break;
    default:
        break;
    }
}

void events_init_screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_btn_set, screen_imgbtn_set_event_handler, LV_EVENT_ALL, ui);
}

void events_init_set_screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_set_btn_back, screen_imgbtn_back_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_set_sw_bettrty_enable, screen_sw_batteryenable_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_set_ddlist_wifi_ssid, screen_ddlist_wifi_event_handler, LV_EVENT_ALL, ui);
    // lv_obj_add_event_cb(ui->screen_set_btn_sd, screen_btn_sd_event_handler, LV_EVENT_ALL, ui);
}

void events_init_wifi_input_screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_wifi_btn_cancel, screen_btn_cancel_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_wifi_btn_select, screen_btn_select_event_handler, LV_EVENT_ALL, ui);
}