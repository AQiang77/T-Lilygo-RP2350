/*
 * Copyright 2024 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui.h"
#include "event_init.h"
#include "Color.h"
#include "widgets_init.h"

extern String wifi_ssid_buf;

void ui_init_style(lv_style_t * style)
{
    if (style->prop_cnt > 1)
        lv_style_reset(style);
    else
        lv_style_init(style);
}

void gui_Set_interface(lv_ui *ui)
{
  // Write codes screen_set
  ui->screen_set = lv_obj_create(NULL);
  lv_obj_set_size(ui->screen_set, 480, 222);
  lv_obj_set_scrollbar_mode(ui->screen_set, LV_SCROLLBAR_MODE_OFF);

  // Write style for screen_set, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(ui->screen_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set, lv_color_hex(0xb400ff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_label__background_2
  ui->screen_set_label__background_2 = lv_label_create(ui->screen_set);
  lv_label_set_text(ui->screen_set_label__background_2, "");
  lv_label_set_long_mode(ui->screen_set_label__background_2, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(ui->screen_set_label__background_2, 0, 0);
  lv_obj_set_size(ui->screen_set_label__background_2, 480, 222);

  // Write style for screen_set_label__background_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui->screen_set_label__background_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_label__background_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui->screen_set_label__background_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(ui->screen_set_label__background_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui->screen_set_label__background_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_label__background_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_label__background_2, lv_color_hex(0x00ffee), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_label__background_2, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_color(ui->screen_set_label__background_2, lv_color_hex(0xd000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_main_stop(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_stop(ui->screen_set_label__background_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_label__background_3
  ui->screen_set_label__background_3 = lv_label_create(ui->screen_set);
  lv_label_set_text(ui->screen_set_label__background_3, "");
  lv_label_set_long_mode(ui->screen_set_label__background_3, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(ui->screen_set_label__background_3, 5, 5);
  lv_obj_set_size(ui->screen_set_label__background_3, 470, 212);

  // Write style for screen_set_label__background_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_label__background_3, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui->screen_set_label__background_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_label__background_3, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui->screen_set_label__background_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(ui->screen_set_label__background_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui->screen_set_label__background_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_label__background_3, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_label__background_3, lv_color_hex(0x161616), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_label__background_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_btn_back
  ui->screen_set_btn_back = lv_btn_create(ui->screen_set);
  ui->screen_set_btn_back_label = lv_label_create(ui->screen_set_btn_back);
  lv_label_set_text(ui->screen_set_btn_back_label, "<< Back ");
  lv_label_set_long_mode(ui->screen_set_btn_back_label, LV_LABEL_LONG_WRAP);
  lv_obj_align(ui->screen_set_btn_back_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_pad_all(ui->screen_set_btn_back, 0, LV_STATE_DEFAULT);
  lv_obj_set_width(ui->screen_set_btn_back_label, LV_PCT(100));
  lv_obj_set_pos(ui->screen_set_btn_back, 10, 12);
  lv_obj_set_size(ui->screen_set_btn_back, 80, 30);

  // Write style for screen_set_btn_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(ui->screen_set_btn_back, 174, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_btn_back, lv_color_hex(0x4300a8), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_back, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->screen_set_btn_back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_btn_back, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_btn_back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui->screen_set_btn_back, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_btn_back, &lv_font_Acme_Regular_16, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui->screen_set_btn_back, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui->screen_set_btn_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_cont_label_list
  ui->screen_set_cont_label_list = lv_obj_create(ui->screen_set);
  lv_obj_set_pos(ui->screen_set_cont_label_list, 10, 50);
  lv_obj_set_size(ui->screen_set_cont_label_list, 460, 160);
  lv_obj_set_scrollbar_mode(ui->screen_set_cont_label_list, LV_SCROLLBAR_MODE_AUTO);

  // Write style for screen_set_cont_label_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_cont_label_list, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_cont_label_list, 231, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_cont_label_list, lv_color_hex(0x005cff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_label_list, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_color(ui->screen_set_cont_label_list, lv_color_hex(0xf9cef4), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_main_stop(ui->screen_set_cont_label_list, 31, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_stop(ui->screen_set_cont_label_list, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_cont_label_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_cont_lable
  ui->screen_set_cont_lable = lv_obj_create(ui->screen_set_cont_label_list);
  lv_obj_set_pos(ui->screen_set_cont_lable, 5, 10);
  lv_obj_set_size(ui->screen_set_cont_lable, 450, 40);
  lv_obj_set_scrollbar_mode(ui->screen_set_cont_lable, LV_SCROLLBAR_MODE_OFF);

  // Write style for screen_set_cont_lable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_cont_lable, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_cont_lable, 126, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_cont_lable, lv_color_hex(0x3a421e), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_lable, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_cont_lable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_sw_bettrty_enable
  ui->screen_set_sw_bettrty_enable = lv_switch_create(ui->screen_set_cont_lable);
  lv_obj_set_pos(ui->screen_set_sw_bettrty_enable, 360, 5);
  lv_obj_set_size(ui->screen_set_sw_bettrty_enable, 80, 30);
  lv_obj_add_state(ui->screen_set_sw_bettrty_enable, LV_STATE_DEFAULT);

  // Write style for screen_set_sw_bettrty_enable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(ui->screen_set_sw_bettrty_enable, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_sw_bettrty_enable, lv_color_hex(0xbcbcbc), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_sw_bettrty_enable, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->screen_set_sw_bettrty_enable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_sw_bettrty_enable, 22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_sw_bettrty_enable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write style for screen_set_sw_bettrty_enable, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
  lv_obj_set_style_bg_opa(ui->screen_set_sw_bettrty_enable, 239, LV_PART_INDICATOR | LV_STATE_CHECKED);
  lv_obj_set_style_bg_color(ui->screen_set_sw_bettrty_enable, lv_color_hex(0x0052e4), LV_PART_INDICATOR | LV_STATE_CHECKED);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_sw_bettrty_enable, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
  lv_obj_set_style_border_width(ui->screen_set_sw_bettrty_enable, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

  // Write style for screen_set_sw_bettrty_enable, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(ui->screen_set_sw_bettrty_enable, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_sw_bettrty_enable, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_sw_bettrty_enable, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->screen_set_sw_bettrty_enable, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_sw_bettrty_enable, 10, LV_PART_KNOB | LV_STATE_DEFAULT);

  // Write codes screen_set_label_bettrty_enable
  ui->screen_set_label_bettrty_enable = lv_label_create(ui->screen_set_cont_lable);
  lv_label_set_text(ui->screen_set_label_bettrty_enable, "Enable Charge");
  // lv_label_set_long_mode(ui->screen_set_label_bettrty_enable, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(ui->screen_set_label_bettrty_enable, 10, 10);
  lv_obj_set_size(ui->screen_set_label_bettrty_enable, 150, 20);

  // Write style for screen_set_label_bettrty_enable, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_label_bettrty_enable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_label_bettrty_enable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui->screen_set_label_bettrty_enable, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui->screen_set_label_bettrty_enable, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_label_bettrty_enable, &lv_font_Acme_Regular_18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(ui->screen_set_label_bettrty_enable, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(ui->screen_set_label_bettrty_enable, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


  // Write codes screen_set_cont_set_wifi
  ui->screen_set_cont_set_wifi = lv_obj_create(ui->screen_set_cont_label_list);
  lv_obj_set_pos(ui->screen_set_cont_set_wifi, 5, 60);
  lv_obj_set_size(ui->screen_set_cont_set_wifi, 450, 40);
  lv_obj_set_scrollbar_mode(ui->screen_set_cont_set_wifi, LV_SCROLLBAR_MODE_OFF);

  // Write style for screen_set_cont_set_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_cont_set_wifi, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_cont_set_wifi, 126, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_cont_set_wifi, lv_color_hex(0x3a421e), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_set_wifi, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_cont_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_label_set_wifi
  ui->screen_set_label_set_wifi = lv_label_create(ui->screen_set_cont_set_wifi);
  lv_label_set_text(ui->screen_set_label_set_wifi, "WIFI_SSID");
  lv_label_set_long_mode(ui->screen_set_label_set_wifi, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(ui->screen_set_label_set_wifi, 10, 10);
  lv_obj_set_size(ui->screen_set_label_set_wifi, 200, 20);

  // Write style for screen_set_label_set_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui->screen_set_label_set_wifi, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_label_set_wifi, &lv_font_Acme_Regular_18, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui->screen_set_label_set_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(ui->screen_set_label_set_wifi, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(ui->screen_set_label_set_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(ui->screen_set_label_set_wifi, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write codes screen_set_ddlist_wifi_ssid
  ui->screen_set_ddlist_wifi_ssid = lv_dropdown_create(ui->screen_set_cont_set_wifi);
  lv_dropdown_set_options(ui->screen_set_ddlist_wifi_ssid, wifi_ssid_buf.c_str());
  lv_obj_set_pos(ui->screen_set_ddlist_wifi_ssid, 240, 5);
  lv_obj_set_size(ui->screen_set_ddlist_wifi_ssid, 200, 30);

  // Write style for screen_set_ddlist_wifi_ssid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_text_color(ui->screen_set_ddlist_wifi_ssid, lv_color_hex(0x0D3055), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui->screen_set_ddlist_wifi_ssid, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(ui->screen_set_ddlist_wifi_ssid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui->screen_set_ddlist_wifi_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(ui->screen_set_ddlist_wifi_ssid, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui->screen_set_ddlist_wifi_ssid, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(ui->screen_set_ddlist_wifi_ssid, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui->screen_set_ddlist_wifi_ssid, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui->screen_set_ddlist_wifi_ssid, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui->screen_set_ddlist_wifi_ssid, lv_color_hex(0xbcbcbc), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui->screen_set_ddlist_wifi_ssid, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(ui->screen_set_ddlist_wifi_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Write style state: LV_STATE_CHECKED for &style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked
  static lv_style_t style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked;
  ui_init_style(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked);

  lv_style_set_border_width(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, 1);
  lv_style_set_border_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, 255);
  lv_style_set_border_color(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
  lv_style_set_border_side(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
  lv_style_set_radius(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, 3);
  lv_style_set_bg_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, 255);
  lv_style_set_bg_color(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, lv_color_hex(0x00a1b5));
  lv_style_set_bg_grad_dir(&style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, LV_GRAD_DIR_NONE);
  lv_obj_add_style(lv_dropdown_get_list(ui->screen_set_ddlist_wifi_ssid), &style_screen_set_ddlist_wifi_ssid_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

  // // Write style state: LV_STATE_DEFAULT for &style_screen_set_ddlist_wifi_ssid_extra_list_main_default
  static lv_style_t style_screen_set_ddlist_wifi_ssid_extra_list_main_default;
  ui_init_style(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default);

  lv_style_set_max_height(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 90);
  lv_style_set_text_color(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, lv_color_hex(0x0D3055));
  lv_style_set_text_font(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, &lv_font_montserratMedium_12);
  lv_style_set_text_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 255);
  lv_style_set_border_width(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 1);
  lv_style_set_border_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 255);
  lv_style_set_border_color(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, lv_color_hex(0xe1e6ee));
  lv_style_set_border_side(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, LV_BORDER_SIDE_FULL);
  lv_style_set_radius(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 3);
  lv_style_set_bg_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, 255);
  lv_style_set_bg_color(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, lv_color_hex(0xffffff));
  lv_style_set_bg_grad_dir(&style_screen_set_ddlist_wifi_ssid_extra_list_main_default, LV_GRAD_DIR_NONE);
  lv_obj_add_style(lv_dropdown_get_list(ui->screen_set_ddlist_wifi_ssid), &style_screen_set_ddlist_wifi_ssid_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

  // // Write style state: LV_STATE_DEFAULT for &style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default
  static lv_style_t style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default;
  ui_init_style(&style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default);

  lv_style_set_radius(&style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default, 3);
  lv_style_set_bg_opa(&style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default, 255);
  lv_style_set_bg_color(&style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
  lv_style_set_bg_grad_dir(&style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
  lv_obj_add_style(lv_dropdown_get_list(ui->screen_set_ddlist_wifi_ssid), &style_screen_set_ddlist_wifi_ssid_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);


// //Write codes screen_set_cont_set_sd
//     ui->screen_set_cont_set_sd = lv_obj_create(ui->screen_set_cont_label_list);
//     lv_obj_set_pos(ui->screen_set_cont_set_sd, 4, 109);
//     lv_obj_set_size(ui->screen_set_cont_set_sd, 450, 40);
//     lv_obj_set_scrollbar_mode(ui->screen_set_cont_set_sd, LV_SCROLLBAR_MODE_OFF);

//     //Write style for screen_set_cont_set_sd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
//     lv_obj_set_style_border_width(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_radius(ui->screen_set_cont_set_sd, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(ui->screen_set_cont_set_sd, 126, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(ui->screen_set_cont_set_sd, lv_color_hex(0x3a421e), LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_grad_dir(ui->screen_set_cont_set_sd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_top(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_bottom(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_left(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_right(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(ui->screen_set_cont_set_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

//     //Write codes screen_set_label_sd
//     ui->screen_set_label_sd = lv_label_create(ui->screen_set_cont_set_sd);
//     lv_label_set_text(ui->screen_set_label_sd, "SD");
//     lv_label_set_long_mode(ui->screen_set_label_sd, LV_LABEL_LONG_WRAP);
//     lv_obj_set_pos(ui->screen_set_label_sd, 10, 10);
//     lv_obj_set_size(ui->screen_set_label_sd, 97, 20);

//     //Write style for screen_set_label_sd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
//     lv_obj_set_style_border_width(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_radius(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(ui->screen_set_label_sd, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_font(ui->screen_set_label_sd, &lv_font_Acme_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_opa(ui->screen_set_label_sd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_letter_space(ui->screen_set_label_sd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_line_space(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(ui->screen_set_label_sd, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_opa(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_top(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_right(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_bottom(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_pad_left(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(ui->screen_set_label_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

//     //Write codes screen_set_btn_sd
//     ui->screen_set_btn_sd = lv_btn_create(ui->screen_set_cont_set_sd);
//     ui->screen_set_btn_sd_label = lv_label_create(ui->screen_set_btn_sd);
//     lv_label_set_text(ui->screen_set_btn_sd_label, "OPEN");
//     lv_label_set_long_mode(ui->screen_set_btn_sd_label, LV_LABEL_LONG_WRAP);
//     lv_obj_align(ui->screen_set_btn_sd_label, LV_ALIGN_CENTER, 0, 0);
//     lv_obj_set_style_pad_all(ui->screen_set_btn_sd, 0, LV_STATE_DEFAULT);
//     lv_obj_set_width(ui->screen_set_btn_sd_label, LV_PCT(100));
//     lv_obj_set_pos(ui->screen_set_btn_sd, 360, 5);
//     lv_obj_set_size(ui->screen_set_btn_sd, 80, 30);

//     //Write style for screen_set_btn_sd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
//     lv_obj_set_style_bg_opa(ui->screen_set_btn_sd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_color(ui->screen_set_btn_sd, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_bg_grad_dir(ui->screen_set_btn_sd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_border_width(ui->screen_set_btn_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_radius(ui->screen_set_btn_sd, 22, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_shadow_width(ui->screen_set_btn_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_color(ui->screen_set_btn_sd, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_font(ui->screen_set_btn_sd, &lv_font_Acme_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_opa(ui->screen_set_btn_sd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
//     lv_obj_set_style_text_align(ui->screen_set_btn_sd, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

  // Update current screen layout.
  lv_obj_update_layout(ui->screen_set);

  // Init events for screen.
  events_init_set_screen(ui);
}
