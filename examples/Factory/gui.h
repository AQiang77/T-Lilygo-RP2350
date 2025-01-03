/**
 * @file      gui.h
 * @author    Lq
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xinyuan Electronic Technology Co., Ltd
 * @date      2023-10-12
 *
 */
#include <Arduino.h>
#include "lvgl.h"
#include <stdio.h>

#pragma once
typedef struct
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
}Time_info;
extern Time_info time_info;
extern char week[4];
extern char str_mon[4];

typedef struct
{
	lv_obj_t *srceen_check;
	lv_obj_t *srceen_cont_check_list;
	lv_obj_t *srceen_label_check_title;

	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_label_background_0;
	lv_obj_t *screen_label_background_1;
	lv_obj_t *screen_cont_time;
	lv_obj_t *screen_cont_info;
	lv_obj_t *screen_cont_pmu;
	lv_obj_t *screen_label_soc_temp;
	lv_obj_t *screen_label_temp_num;
	lv_obj_t *screen_cont_wifi;
	lv_obj_t *screen_cont_battery_info;
	lv_obj_t *screen_label_time_num;
	lv_obj_t *screen_line_blue;
	lv_obj_t *screen_label_data;
	lv_obj_t *screen_label_year;
	lv_obj_t *screen_label_battery_VBUS;
	lv_obj_t *screen_label_battery_VBUS_raw;
	lv_obj_t *screen_label_battery_VBAT;
	lv_obj_t *screen_label_battery_VBAT_raw;
	lv_obj_t *screen_label_battery_TargetVoltage;
	lv_obj_t *screen_label_battery_TargetVoltage_raw;
	lv_obj_t *screen_label_battery_ChargeCurrent;
	lv_obj_t *screen_label_battery_ChargeCurrent_raw;
	lv_obj_t *screen_label_mac_raw;
	lv_obj_t *screen_label_wifissid;
	lv_obj_t *screen_label_wifissid_raw;
	lv_obj_t *screen_label_mac;
	lv_obj_t *screen_label_version;
	lv_obj_t *screen_label_version_raw;
	lv_obj_t *screen_cont_logo;
	lv_obj_t *screen_label_device;
	lv_obj_t *screen_img_lilygo;
	lv_obj_t *screen_cont_set;
	lv_obj_t *screen_btn_set;
	lv_obj_t *screen_btn_set_label;
	lv_obj_t *screen_img_set;
	lv_obj_t *screen_line_parting_line;
	lv_obj_t *screen_cont_battery;
	lv_obj_t *screen_bar_battery;
	lv_obj_t *screen_label_battety_line;
	lv_obj_t *screen_label_battery;
	lv_obj_t* screen_image_flash_charge;

	lv_obj_t *g_kb_screen_set;
	lv_obj_t *screen_set_cont_set_wifi;
	lv_obj_t *screen_set_label_set_wifi;
	lv_obj_t *screen_set_ddlist_wifi_ssid;

	lv_obj_t *screen_set;
	bool screen_set_del;
	lv_obj_t *screen_set_label__background_2;
	lv_obj_t *screen_set_label__background_3;
	lv_obj_t *screen_set_btn_back;
	lv_obj_t *screen_set_btn_back_label;
	lv_obj_t *screen_set_cont_label_list;
	lv_obj_t *screen_set_cont_lable;
	lv_obj_t *screen_set_sw_bettrty_enable;
	lv_obj_t *screen_set_label_bettrty_enable;
	lv_obj_t *screen_set_cont_set_sd;
	lv_obj_t *screen_set_label_sd;
	lv_obj_t *screen_set_btn_sd;
	lv_obj_t *screen_set_btn_sd_label;

	lv_obj_t *screen_wifi;
	lv_obj_t *screen_wifi_keyboard;
	lv_obj_t *screen_wifi_ta_wifi_password;
	lv_obj_t *screen_wifi_label_cancel;
	lv_obj_t *screen_wifi_label_select;
	lv_obj_t *screen_wifi_btn_select;
	lv_obj_t *screen_wifi_btn_cancel;
	lv_obj_t *screen_wifi_lable_wait_connect;

	lv_obj_t *screen_sd;
	lv_obj_t *screen_sd_cont;
	lv_obj_t *screen_sd_label_background_1;
	lv_obj_t *srceen_sd_list;

	lv_obj_t *screen_test;
} lv_ui;


void Check_Moudle_gui(lv_ui *ui);
void gui_Main_interface(lv_ui *ui);
void gui_Set_interface(lv_ui *ui);
void gui_SD_interface(lv_ui *ui);
void WIFI_input_gui(lv_ui *ui);
void ui_init_style(lv_style_t *style);
extern bool esp_get_ntp_time();

LV_IMG_DECLARE(_46522448_alpha_100x100);
LV_IMG_DECLARE(_setup_00eeff_alpha_40x40);
LV_IMG_DECLARE(_flash_alpha_40x40);

// LV_IMG_DECLARE(_LILYGO_alpha_100x100);
// LV_IMG_DECLARE(_setup_alpha_43x37);
// LV_IMG_DECLARE(_LILYGO_alpha_95x45);
// LV_IMG_DECLARE(_setup_alpha_60x60);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_10)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_12)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_14)
LV_FONT_DECLARE(lv_font_Alatsi_Regular_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_10)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_24)
LV_FONT_DECLARE(lv_font_Acme_Regular_16)
LV_FONT_DECLARE(lv_font_Acme_Regular_18)
LV_FONT_DECLARE(lv_font_Acme_Regular_19)
LV_FONT_DECLARE(lv_font_Acme_Regular_24)
LV_FONT_DECLARE(lv_font_Acme_Regular_35)
LV_FONT_DECLARE(lv_font_Acme_Regular_40)
LV_FONT_DECLARE(lv_font_Abel_regular_18)
LV_FONT_DECLARE(lv_font_Abel_regular_30)
LV_FONT_DECLARE(lv_font_ArchitectsDaughter_18)