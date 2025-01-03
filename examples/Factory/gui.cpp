#include <Arduino.h>
#include <lvgl.h>
#include <time.h>
#include <XPowersLib.h>
#include <WiFiEspAT.h>
#include "utilities.h"
#include "gui.h"
#include "event_init.h"

extern bool Expand_status, PMU_status, Touch_status, SD_status, WiFi_status, Screen_status;

extern PowersSY6970 PMU;
extern lv_ui ui;
extern String macAddress(void);
extern String get_WIFI_SSID(void);
extern WiFiClass WiFi;
extern IPAddress ip;
extern bool WiFi_connect_status;
extern bool bettary_enable;

extern uint16_t max_voltage;
extern uint16_t min_voltage;
extern uint16_t voltage_step_size;
extern uint8_t percentage_voltage;
uint8_t update_voltage = 0;

Time_info time_info;
char week[4];
char str_mon[4];

String getModel()
{
    SerialAT.println("AT+GMR");
    String str = SerialAT.readString();
    int idx = str.indexOf("ESP");
    if (idx == -1)
    {
        return "None";
    }
    str = str.substring(idx, str.indexOf(" ", idx));
    return str;
}

void gui_check_lable(lv_obj_t *parent, String text, bool status)
{
    lv_obj_t *scr = lv_obj_create(parent);
    lv_obj_set_scroll_dir(scr, LV_DIR_NONE);                                                // 设置滚动方向
    lv_obj_set_size(scr, LV_PCT(100), lv_font_get_line_height(&lv_font_montserrat_28) + 2); // 设置parent对象大小
    lv_obj_set_style_bg_color(scr, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);      // 设置背景颜色
    lv_obj_set_style_border_width(scr, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scr, lv_color_white(), LV_PART_MAIN);

    lv_obj_t *moudle_name = lv_label_create(scr);
    // lv_obj_add_style(moudle_name, &style, LV_PART_MAIN);
    lv_obj_set_style_text_font(moudle_name, &lv_font_montserrat_16, 0);
    lv_label_set_recolor(moudle_name, true);
    lv_label_set_text(moudle_name, text.c_str());
    lv_obj_align(moudle_name, LV_ALIGN_LEFT_MID, 0, 0); // 设置对齐方式

    lv_obj_t *moudle_status = lv_label_create(scr);
    lv_label_set_recolor(moudle_status, true);
    lv_label_set_text(moudle_status, status ? "[ #00FF00  OK#  ]" : "[ #FF0000  ERROR#  ]");
    lv_obj_align(moudle_status, LV_ALIGN_RIGHT_MID, 0, 0); // 设置对齐方式

    lv_obj_scroll_to_y(parent, lv_disp_get_ver_res(NULL), LV_ANIM_ON);

    int i = 200;
    while (i--)
    {
        lv_task_handler();
        // sleep_us(1000);
        delay(1);
    }
}

void Check_Moudle_gui(lv_ui *ui)
{
    // Serial.println("Check_Moudle_gui");
    ui->srceen_check = lv_obj_create(NULL);
    lv_obj_set_size(ui->srceen_check, 480, 222);
    lv_obj_set_scrollbar_mode(ui->srceen_check, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_color(ui->srceen_check, lv_color_hex(0xf5c82d), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->srceen_check, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->srceen_check, lv_color_hex(0x31311a), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_scr_load(ui->srceen_check);

    ui->srceen_label_check_title = lv_label_create(ui->srceen_check);
    lv_obj_set_pos(ui->srceen_label_check_title, 10, 10);
    lv_obj_set_size(ui->srceen_label_check_title, 460, 30);
    lv_label_set_text(ui->srceen_label_check_title, "Check Moudle");
    lv_obj_set_style_text_font(ui->srceen_label_check_title, &lv_font_Acme_Regular_24, 0);
    lv_obj_set_style_text_align(ui->srceen_label_check_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(ui->srceen_label_check_title, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_radius(ui->srceen_label_check_title, 5, LV_PART_MAIN | LV_STATE_DEFAULT); // 设置圆角
    lv_obj_set_style_bg_opa(ui->srceen_label_check_title, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->srceen_label_check_title, lv_color_white(), LV_PART_MAIN); // 设置背景颜色
    lv_obj_remove_style(ui->srceen_label_check_title, 0, LV_PART_SCROLLBAR);                 // 移除滚动条
    lv_obj_set_style_border_opa(ui->srceen_label_check_title, LV_OPA_TRANSP, LV_PART_MAIN);  // 设置边框透明

    ui->srceen_cont_check_list = lv_obj_create(ui->srceen_check);
    lv_obj_set_pos(ui->srceen_cont_check_list, 10, 50);
    lv_obj_set_size(ui->srceen_cont_check_list, 460, 162);
    lv_obj_set_style_radius(ui->srceen_cont_check_list, 15, LV_PART_MAIN | LV_STATE_DEFAULT); // 设置圆角
    lv_obj_set_style_bg_opa(ui->srceen_cont_check_list, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->srceen_cont_check_list, lv_color_white(), LV_PART_MAIN); // 设置背景颜色
    lv_obj_set_scrollbar_mode(ui->srceen_cont_check_list, LV_SCROLLBAR_MODE_AUTO);
    lv_obj_set_style_border_opa(ui->srceen_cont_check_list, LV_OPA_TRANSP, LV_PART_MAIN); // 设置边框透明
    lv_obj_set_flex_flow(ui->srceen_cont_check_list, LV_FLEX_FLOW_COLUMN);                // 容器竖直排列

    gui_check_lable(ui->srceen_cont_check_list, "Expand IO Moudle", Expand_status);
    gui_check_lable(ui->srceen_cont_check_list, "Power management", PMU_status);
    gui_check_lable(ui->srceen_cont_check_list, "Capacitive Touch", Touch_status);
    gui_check_lable(ui->srceen_cont_check_list, "WiFi Module [ #00ff00  " + getModel() + "_V" + String(WiFi.firmwareVersion()) + "# ]", WiFi_status);
    gui_check_lable(ui->srceen_cont_check_list, "SD Card", SD_status);
}

void timer_cb(lv_timer_t *timer)
{
    // Serial.println("timer_cb");
    uint8_t static time_count = 0;
    time_count++;

    time_info.tm_sec++;
    if (time_info.tm_sec > 59)
    {
        time_info.tm_sec = 0;
        time_info.tm_min++;
        if (time_info.tm_min > 59)
        {
            time_info.tm_min = 0;
            time_info.tm_hour++;
            if (time_info.tm_hour > 23)
            {
                time_info.tm_hour = 0;
                esp_get_ntp_time();
            }
        }
    }
    lv_label_set_text_fmt(ui.screen_label_time_num, "%02d:%02d:%02d", time_info.tm_hour, time_info.tm_min, time_info.tm_sec);
    lv_label_set_text_fmt(ui.screen_label_data, "%s %02d", String(str_mon).c_str(), time_info.tm_mday);
    lv_label_set_text_fmt(ui.screen_label_year, "%s\r\n%4d", String(week).c_str(), time_info.tm_year);

    if (time_count >= 5)
    {
        time_count = 0;
        lv_label_set_text_fmt(ui.screen_label_temp_num, "%2.1f C", analogReadTemp());
        lv_label_set_text_fmt(ui.screen_label_battery_VBUS_raw, "%d mV", PMU.getVbusVoltage());
        lv_label_set_text_fmt(ui.screen_label_battery_VBAT_raw, "%d mV", PMU.getBattVoltage());
        lv_label_set_text_fmt(ui.screen_label_battery_TargetVoltage_raw, "%d mV", PMU.getChargeTargetVoltage());
        lv_label_set_text_fmt(ui.screen_label_battery_ChargeCurrent_raw, "%d mA", PMU.getChargerConstantCurr());
    }

    // Serial.printf("getBattVoltage():%d\n",PMU.getBattVoltage());
    if (WiFi_connect_status)
    {
        lv_label_set_text_fmt(ui.screen_label_wifissid_raw, "%s", get_WIFI_SSID().c_str());
        lv_label_set_text_fmt(ui.screen_label_mac_raw, "%s", WiFi.localIP().toString().c_str());
        lv_label_set_text_fmt(ui.screen_label_version_raw, "%s", WiFi.firmwareVersion());
    }

    if (bettary_enable)
    {
        // voltage 0mv - 3840mv
        PMU.enableCharge(); // 开启充电
        // lv_obj_clear_flag(ui.screen_image_flash_charge, LV_OBJ_FLAG_HIDDEN);
        // PMU.enableStatLed();
        percentage_voltage = PMU.getBattVoltage() / voltage_step_size;
        update_voltage++;
        if (update_voltage >= 3)
        {
            if (percentage_voltage >= 100)
                percentage_voltage = 100;
            lv_bar_set_value(ui.screen_bar_battery, percentage_voltage, LV_ANIM_ON);
            lv_label_set_text_fmt(ui.screen_label_battery, "%d%%", percentage_voltage);
            update_voltage = 0;
        }
    }
    else
    {
        // lv_obj_add_flag(ui.screen_image_flash_charge, LV_OBJ_FLAG_HIDDEN);
        PMU.disableCharge(); // 关闭充电
        // PMU.disableStatLed();
        percentage_voltage = PMU.getBattVoltage() / voltage_step_size;
        lv_bar_set_value(ui.screen_bar_battery, percentage_voltage, LV_ANIM_ON);
        lv_label_set_text_fmt(ui.screen_label_battery, "%d%%", percentage_voltage);
    }
}

void gui_Main_interface(lv_ui *ui)
{
    lv_timer_t *timer = lv_timer_create(timer_cb, 1000, NULL);
    lv_timer_ready(timer);

    // Write codes screen_back_ground
    ui->screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen, 480, 222);
    lv_obj_set_pos(ui->screen, 0, 221);
    lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_background_0
    ui->screen_label_background_0 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_background_0, "");
    lv_label_set_long_mode(ui->screen_label_background_0, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_background_0, 0, 0);
    lv_obj_set_size(ui->screen_label_background_0, 480, 222);

    // Write style for screen_label_background_0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_background_0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_background_0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_background_0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_background_0, lv_color_hex(0x5905d6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_background_0, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_label_background_0, lv_color_hex(0xab15b4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_label_background_0, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_label_background_0, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_background_1
    ui->screen_label_background_1 = lv_label_create(ui->screen);
    lv_label_set_text(ui->screen_label_background_1, "");
    lv_label_set_long_mode(ui->screen_label_background_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_background_1, 5, 5);
    lv_obj_set_size(ui->screen_label_background_1, 470, 212);

    // Write style for screen_label_background_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_background_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_background_1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_background_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_background_1, lv_color_hex(0x191919), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_background_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_logo
    ui->screen_cont_logo = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_logo, 15, 10);
    lv_obj_set_size(ui->screen_cont_logo, 220, 200);
    lv_obj_set_scrollbar_mode(ui->screen_cont_logo, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_logo, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_logo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_logo, lv_color_hex(0x413b75), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_logo, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_cont_logo, lv_color_hex(0x6e004d), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_cont_logo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_logo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_device
    ui->screen_label_device = lv_label_create(ui->screen_cont_logo);
    lv_label_set_text(ui->screen_label_device, "LILYGO\nT-Pico2\nESP32C3");
    lv_label_set_long_mode(ui->screen_label_device, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_device, 120, 10);
    lv_obj_set_size(ui->screen_label_device, 90, 100);

    // Write style for screen_label_device, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_device, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_device, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_device, lv_color_hex(0xf200ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_device, &lv_font_Acme_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_device, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_device, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_device, 18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_device, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_device, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_device, lv_color_hex(0x2d0081), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_device, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_label_device, lv_color_hex(0x7a2a2a), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_label_device, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_label_device, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_img_lilygo
    ui->screen_img_lilygo = lv_img_create(ui->screen_cont_logo);
    lv_obj_add_flag(ui->screen_img_lilygo, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_lilygo, &_46522448_alpha_100x100);
    lv_img_set_pivot(ui->screen_img_lilygo, 50, 50);
    lv_img_set_angle(ui->screen_img_lilygo, 0);
    lv_obj_set_pos(ui->screen_img_lilygo, 10, 10);
    lv_obj_set_size(ui->screen_img_lilygo, 100, 100);

    // Write style for screen_img_lilygo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_lilygo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_lilygo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_lilygo, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_lilygo, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_set
    ui->screen_cont_set = lv_obj_create(ui->screen_cont_logo);
    lv_obj_set_pos(ui->screen_cont_set, 10, 140);
    lv_obj_set_size(ui->screen_cont_set, 100, 40);
    lv_obj_set_scrollbar_mode(ui->screen_cont_set, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_set, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_set, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_set, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_btn_set
    ui->screen_btn_set = lv_btn_create(ui->screen_cont_set);
    ui->screen_btn_set_label = lv_label_create(ui->screen_btn_set);
    lv_label_set_text(ui->screen_btn_set_label, "Setting              ");
    lv_label_set_long_mode(ui->screen_btn_set_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_btn_set_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_btn_set, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_btn_set_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_btn_set, 0, 0);
    lv_obj_set_size(ui->screen_btn_set, 100, 40);

    // Write style for screen_btn_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_btn_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_btn_set, lv_color_hex(0x8300ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_btn_set, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_btn_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_btn_set, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_btn_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_btn_set, lv_color_hex(0x00eeff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_btn_set, &lv_font_Acme_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_btn_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_btn_set, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_img_set
    ui->screen_img_set = lv_img_create(ui->screen_cont_set);
    lv_obj_add_flag(ui->screen_img_set, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_img_set, &_setup_00eeff_alpha_40x40);
    lv_img_set_pivot(ui->screen_img_set, 50, 50);
    lv_img_set_angle(ui->screen_img_set, 0);
    lv_obj_set_pos(ui->screen_img_set, 60, 0);
    lv_obj_set_size(ui->screen_img_set, 40, 40);

    // Write style for screen_img_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_img_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_img_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_img_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_img_set, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_line_parting_line
    ui->screen_line_parting_line = lv_line_create(ui->screen_cont_logo);
    static lv_point_t screen_line_parting_line[] = {
        {0, 0},
        {210, 0},
    };
    lv_line_set_points(ui->screen_line_parting_line, screen_line_parting_line, 2);
    lv_obj_set_pos(ui->screen_line_parting_line, 5, 125);
    lv_obj_set_size(ui->screen_line_parting_line, 208, 10);

    // Write style for screen_line_parting_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_line_parting_line, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_line_parting_line, lv_color_hex(0xd306a0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_line_parting_line, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_line_parting_line, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_battery
    ui->screen_cont_battery = lv_obj_create(ui->screen_cont_logo);
    lv_obj_set_pos(ui->screen_cont_battery, 120, 145);
    lv_obj_set_size(ui->screen_cont_battery, 100, 30);
    lv_obj_set_scrollbar_mode(ui->screen_cont_battery, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_bar_battery
    ui->screen_bar_battery = lv_bar_create(ui->screen_cont_battery);
    lv_obj_set_style_anim_time(ui->screen_bar_battery, 1000, 0);
    lv_bar_set_mode(ui->screen_bar_battery, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_bar_battery, 0, 100);
    lv_bar_set_value(ui->screen_bar_battery, 0, LV_ANIM_ON);
    lv_obj_set_pos(ui->screen_bar_battery, 0, 0);
    lv_obj_set_size(ui->screen_bar_battery, 45, 30);

    // Write style for screen_bar_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_battery, 78, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_battery, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_battery, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_bar_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_bar_battery, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_bar_battery, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_bar_battery, lv_color_hex(0x00ff9a), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_bar_battery, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_bar_battery, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write codes screen_label_battety_line
    ui->screen_label_battety_line = lv_label_create(ui->screen_cont_battery);
    lv_label_set_text(ui->screen_label_battety_line, "");
    lv_label_set_long_mode(ui->screen_label_battety_line, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battety_line, 45, 5);
    lv_obj_set_size(ui->screen_label_battety_line, 4, 20);

    // Write style for screen_label_battety_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_battety_line, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_battety_line, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_battety_line, 81, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_label_battety_line, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_label_battety_line, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_image_flash_charge
    ui->screen_image_flash_charge = lv_img_create(ui->screen_cont_battery);
    lv_obj_add_flag(ui->screen_image_flash_charge, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_image_flash_charge, &_flash_alpha_40x40);
    lv_img_set_pivot(ui->screen_image_flash_charge, 0, 0);
    lv_img_set_angle(ui->screen_image_flash_charge, 900);
    lv_obj_set_pos(ui->screen_image_flash_charge, 40, -5);
    lv_obj_set_size(ui->screen_image_flash_charge, 40, 35);

    // Write style for screen_image_flash_charge, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_image_flash_charge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->screen_image_flash_charge, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_image_flash_charge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_image_flash_charge, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_image_flash_charge, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(ui->screen_image_flash_charge, LV_OBJ_FLAG_HIDDEN);

    // Write codes screen_label_battery
    ui->screen_label_battery = lv_label_create(ui->screen_cont_battery);
    lv_label_set_text_fmt(ui->screen_label_battery, "%d%%", percentage_voltage);
    lv_label_set_long_mode(ui->screen_label_battery, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery, 50, 8);
    lv_obj_set_size(ui->screen_label_battery, 50, 15);

    // Write style for screen_label_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_battery, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery, &lv_font_Alatsi_Regular_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_battery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_battery, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_info
    ui->screen_cont_info = lv_obj_create(ui->screen);
    lv_obj_set_pos(ui->screen_cont_info, 245, 10);
    lv_obj_set_size(ui->screen_cont_info, 220, 200);
    lv_obj_set_scrollbar_mode(ui->screen_cont_info, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_info, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_cont_info, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_cont_info, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_info, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_info, lv_color_hex(0x00ffee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_info, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_cont_info, lv_color_hex(0xd000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_cont_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_time
    ui->screen_cont_time = lv_obj_create(ui->screen_cont_info);
    lv_obj_set_pos(ui->screen_cont_time, 10, 10);
    lv_obj_set_size(ui->screen_cont_time, 200, 100);
    lv_obj_set_scrollbar_mode(ui->screen_cont_time, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_time, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_time, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_time, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_time_num
    ui->screen_label_time_num = lv_label_create(ui->screen_cont_time);
    lv_label_set_text(ui->screen_label_time_num, "00:00:00");
    lv_label_set_long_mode(ui->screen_label_time_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_time_num, 10, 5);
    lv_obj_set_size(ui->screen_label_time_num, 180, 30);

    // Write style for screen_label_time_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_time_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_time_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_time_num, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_time_num, &lv_font_Acme_Regular_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_time_num, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_time_num, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_time_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_time_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_line_blue
    ui->screen_line_blue = lv_line_create(ui->screen_cont_time);
    static lv_point_t screen_line_blue[] = {
        {0, 0},
        {210, 0},
    };
    lv_line_set_points(ui->screen_line_blue, screen_line_blue, 2);
    lv_obj_set_pos(ui->screen_line_blue, 5, 50);
    lv_obj_set_size(ui->screen_line_blue, 190, 5);

    // Write style for screen_line_blue, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_line_blue, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_line_blue, lv_color_hex(0x00cbff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_line_blue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_line_blue, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_year
    ui->screen_label_data = lv_label_create(ui->screen_cont_time);
    lv_label_set_text(ui->screen_label_data, "");
    lv_label_set_long_mode(ui->screen_label_data, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_data, 10, 60);
    lv_obj_set_size(ui->screen_label_data, 110, 30);

    // Write style for screen_label_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_data, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_data, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_data, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_data, &lv_font_Abel_regular_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_data, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_data, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_data, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_data, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_year
    ui->screen_label_year = lv_label_create(ui->screen_cont_time);
    lv_label_set_text(ui->screen_label_year, "");
    lv_label_set_long_mode(ui->screen_label_year, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_year, 125, 55);
    lv_obj_set_size(ui->screen_label_year, 80, 35);

    // Write style for screen_label_year, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_year, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_year, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_year, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_year, &lv_font_ArchitectsDaughter_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_year, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_year, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_year, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_year, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_pmu
    ui->screen_cont_pmu = lv_obj_create(ui->screen_cont_info);
    lv_obj_set_pos(ui->screen_cont_pmu, 10, 120);
    lv_obj_set_size(ui->screen_cont_pmu, 200, 40);
    lv_obj_set_scrollbar_mode(ui->screen_cont_pmu, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_pmu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_pmu, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_pmu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_pmu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_pmu, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_pmu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_soc_temp
    ui->screen_label_soc_temp = lv_label_create(ui->screen_cont_pmu);
    lv_label_set_text(ui->screen_label_soc_temp, "SOC:");
    lv_label_set_long_mode(ui->screen_label_soc_temp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_soc_temp, 10, 10);
    lv_obj_set_size(ui->screen_label_soc_temp, 50, 20);

    // Write style for screen_label_soc_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_soc_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_soc_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_soc_temp, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_soc_temp, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_soc_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_soc_temp, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_soc_temp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_soc_temp, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_temp_num
    ui->screen_label_temp_num = lv_label_create(ui->screen_cont_pmu);
    lv_label_set_text(ui->screen_label_temp_num, "NULL");
    lv_label_set_long_mode(ui->screen_label_temp_num, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_temp_num, 95, 10);
    lv_obj_set_size(ui->screen_label_temp_num, 100, 20);

    // Write style for screen_label_temp_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_temp_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_temp_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_temp_num, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_temp_num, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_temp_num, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_temp_num, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_temp_num, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_temp_num, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_wifi
    ui->screen_cont_wifi = lv_obj_create(ui->screen_cont_info);
    lv_obj_set_pos(ui->screen_cont_wifi, 10, 170);
    lv_obj_set_size(ui->screen_cont_wifi, 200, 130);
    lv_obj_set_scrollbar_mode(ui->screen_cont_wifi, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_wifi, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_wifi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_wifi, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_cont_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_mac_raw
    ui->screen_label_mac_raw = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_mac_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_mac_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_mac_raw, 95, 60);
    lv_obj_set_size(ui->screen_label_mac_raw, 100, 40);

    // Write style for screen_label_mac_raw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_mac_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_mac_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_mac_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_mac_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_mac_raw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_mac_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_mac_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_mac_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_wifissid
    ui->screen_label_wifissid = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_wifissid, "WIFI SSID:");
    lv_label_set_long_mode(ui->screen_label_wifissid, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_wifissid, 10, 10);
    lv_obj_set_size(ui->screen_label_wifissid, 50, 30);

    // Write style for screen_label_wifissid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_wifissid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_wifissid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_wifissid, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_wifissid, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_wifissid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_wifissid, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_wifissid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_wifissid, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_wifissid_raw
    ui->screen_label_wifissid_raw = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_wifissid_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_wifissid_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_wifissid_raw, 95, 10);
    lv_obj_set_size(ui->screen_label_wifissid_raw, 100, 35);

    // Write style for screen_label_wifissid_raw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_wifissid_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_wifissid_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_wifissid_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_wifissid_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_wifissid_raw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_wifissid_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_wifissid_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_wifissid_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_wifissid_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_mac
    ui->screen_label_mac = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_mac, "IP:");
    lv_label_set_long_mode(ui->screen_label_mac, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_mac, 10, 60);
    lv_obj_set_size(ui->screen_label_mac, 50, 25);

    // Write style for screen_label_mac, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_mac, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_mac, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_mac, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_mac, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_mac, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_mac, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_mac, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_mac, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_mac, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_version
    ui->screen_label_version = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_version, "Version:");
    lv_label_set_long_mode(ui->screen_label_version, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_version, 10, 100);
    lv_obj_set_size(ui->screen_label_version, 80, 20);

    // Write style for screen_label_version, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_version, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_version, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_version, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_version, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_version, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_label_version, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_version_raw
    ui->screen_label_version_raw = lv_label_create(ui->screen_cont_wifi);
    lv_label_set_text(ui->screen_label_version_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_version_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_version_raw, 95, 100);
    lv_obj_set_size(ui->screen_label_version_raw, 100, 20);

    // Write style for screen_label_version_raw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_label_version_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_label_version_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_version_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_version_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_label_version_raw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_version_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_label_version_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_version_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_label_version_raw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_cont_battery_info
    ui->screen_cont_battery_info = lv_obj_create(ui->screen_cont_info);
    lv_obj_set_pos(ui->screen_cont_battery_info, 10, 310);
    lv_obj_set_size(ui->screen_cont_battery_info, 200, 160);
    lv_obj_set_scrollbar_mode(ui->screen_cont_battery_info, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_cont_battery_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_cont_battery_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_cont_battery_info, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_cont_battery_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_cont_battery_info, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_cont_battery_info, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_cont_battery_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_cont_battery_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_cont_battery_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_cont_battery_info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_VBUS = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_VBUS, "VBUS:");
    lv_label_set_long_mode(ui->screen_label_battery_VBUS, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_VBUS, 10, 10);
    lv_obj_set_size(ui->screen_label_version, 60, 20);
    lv_obj_set_style_text_align(ui->screen_label_battery_VBUS, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_VBUS, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_battery_VBUS, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_VBUS, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_VBUS_raw = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_VBUS_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_battery_VBUS_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_VBUS_raw, 95, 10);
    lv_obj_set_size(ui->screen_label_battery_VBUS_raw, 100, 20);
    lv_obj_set_style_text_color(ui->screen_label_battery_VBUS_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_VBUS_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_VBUS_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_battery_VBUS_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_VBAT = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_VBAT, "VBAT:");
    lv_label_set_long_mode(ui->screen_label_battery_VBAT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_VBAT, 10, 50);
    lv_obj_set_size(ui->screen_label_version, 60, 20);
    lv_obj_set_style_text_align(ui->screen_label_battery_VBAT, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_VBAT, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_battery_VBAT, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_VBAT, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_VBAT_raw = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_VBAT_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_battery_VBAT_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_VBAT_raw, 95, 50);
    lv_obj_set_size(ui->screen_label_battery_VBAT_raw, 100, 20);
    lv_obj_set_style_text_color(ui->screen_label_battery_VBAT_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_VBAT_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_VBAT_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_battery_VBAT_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_TargetVoltage = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_TargetVoltage, "Target\nVoltage:");
    lv_label_set_long_mode(ui->screen_label_battery_TargetVoltage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_TargetVoltage, 10, 82);
    lv_obj_set_size(ui->screen_label_version, 100, 20);
    lv_obj_set_style_text_align(ui->screen_label_battery_TargetVoltage, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_TargetVoltage, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_battery_TargetVoltage, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_TargetVoltage, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_TargetVoltage_raw = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_TargetVoltage_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_battery_TargetVoltage_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_TargetVoltage_raw, 95, 90);
    lv_obj_set_size(ui->screen_label_battery_TargetVoltage_raw, 100, 20);
    lv_obj_set_style_text_color(ui->screen_label_battery_TargetVoltage_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_TargetVoltage_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_TargetVoltage_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_battery_TargetVoltage_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_ChargeCurrent = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_ChargeCurrent, "Current:");
    lv_label_set_long_mode(ui->screen_label_battery_ChargeCurrent, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_ChargeCurrent, 10, 130);
    lv_obj_set_size(ui->screen_label_version, 100, 20);
    lv_obj_set_style_text_align(ui->screen_label_battery_ChargeCurrent, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_ChargeCurrent, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_label_battery_ChargeCurrent, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_ChargeCurrent, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_label_battery_ChargeCurrent_raw = lv_label_create(ui->screen_cont_battery_info);
    lv_label_set_text(ui->screen_label_battery_ChargeCurrent_raw, "NULL");
    lv_label_set_long_mode(ui->screen_label_battery_ChargeCurrent_raw, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_label_battery_ChargeCurrent_raw, 95, 130);
    lv_obj_set_size(ui->screen_label_battery_ChargeCurrent_raw, 100, 20);
    lv_obj_set_style_text_color(ui->screen_label_battery_ChargeCurrent_raw, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_label_battery_ChargeCurrent_raw, &lv_font_Alatsi_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_label_battery_ChargeCurrent_raw, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_label_battery_ChargeCurrent_raw, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Update current screen layout.
    lv_obj_update_layout(ui->screen);

    // Init events for screen.
    events_init_screen(ui);
}
