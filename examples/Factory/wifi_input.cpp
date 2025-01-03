#include "lvgl.h"
#include <stdio.h>
#include "gui.h"
#include "event_init.h"
#include "Color.h"
#include "widgets_init.h"

void WIFI_input_gui(lv_ui *ui)
{
    // Write codes screen_back_ground
    // Serial.println("WIFI_input_gui");
    ui->screen_wifi = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_wifi, 480, 222);
    lv_obj_set_scrollbar_mode(ui->screen_set, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_bg_color(ui->screen_wifi, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(ui->screen_wifi, 255, LV_PART_MAIN);
    lv_obj_set_style_border_width(ui->screen_wifi, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_set_label__background_2
    ui->screen_set_label__background_2 = lv_label_create(ui->screen_wifi);
    lv_label_set_text(ui->screen_set_label__background_2, "");
    lv_label_set_long_mode(ui->screen_set_label__background_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_set_label__background_2, 0, 0);
    lv_obj_set_size(ui->screen_set_label__background_2, 480, 222);

    // Write style for screen_set_label__background_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label__background_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_label__background_2, lv_color_hex(0x00ffee), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_label__background_2, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_set_label__background_2, lv_color_hex(0xd000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen_set_label__background_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen_set_label__background_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_set_label__background_3
    ui->screen_set_label__background_3 = lv_label_create(ui->screen_wifi);
    lv_label_set_text(ui->screen_set_label__background_3, "");
    lv_label_set_long_mode(ui->screen_set_label__background_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_set_label__background_3, 5, 5);
    lv_obj_set_size(ui->screen_set_label__background_3, 470, 212);

    // Write style for screen_set_label__background_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_set_label__background_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_set_label__background_3, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_set_label__background_3, 102, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_set_label__background_3, lv_color_hex(0x161616), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_set_label__background_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui->screen_wifi_keyboard = lv_keyboard_create(ui->screen_wifi);
    ui->screen_wifi_ta_wifi_password = lv_textarea_create(ui->screen_wifi);

    lv_obj_add_event_cb(ui->screen_wifi_ta_wifi_password, ta_event_cb, LV_EVENT_ALL, ui->screen_wifi_keyboard);

    lv_textarea_set_placeholder_text(ui->screen_wifi_ta_wifi_password, "print your wifi password");
    lv_obj_set_pos(ui->screen_wifi_ta_wifi_password, 10, 10);
    lv_obj_set_size(ui->screen_wifi_ta_wifi_password, 260, 60);
    lv_obj_set_style_text_font(ui->screen_wifi_ta_wifi_password, &lv_font_dejavu_16_persian_hebrew, 0);

    lv_keyboard_set_textarea(ui->screen_wifi_keyboard, ui->screen_wifi_ta_wifi_password);
    lv_obj_set_style_text_font(ui->screen_wifi_keyboard, &lv_font_dejavu_16_persian_hebrew, 0);

    ui->screen_wifi_btn_cancel = lv_btn_create(ui->screen_wifi);
    ui->screen_wifi_label_cancel = lv_label_create(ui->screen_wifi_btn_cancel);
    lv_label_set_text(ui->screen_wifi_label_cancel, "Cancel");
    lv_obj_set_width(ui->screen_wifi_label_cancel, LV_PCT(100));
    lv_obj_set_pos(ui->screen_wifi_btn_cancel, 280, 20);
    lv_obj_set_style_radius(ui->screen_wifi_btn_cancel, 10, LV_PART_MAIN);
    lv_obj_set_size(ui->screen_wifi_btn_cancel, 90, 40);
    lv_obj_set_style_bg_color(ui->screen_wifi_btn_cancel, lv_color_hex(0x176edb), LV_PART_MAIN);

    ui->screen_wifi_btn_select = lv_btn_create(ui->screen_wifi);
    ui->screen_wifi_label_select = lv_label_create(ui->screen_wifi_btn_select);
    lv_label_set_text(ui->screen_wifi_label_select, "Select");
    lv_obj_set_width(ui->screen_wifi_label_select, LV_PCT(100));
    lv_obj_set_pos(ui->screen_wifi_btn_select, 380, 20);
    lv_obj_set_size(ui->screen_wifi_btn_select, 90, 40);
    lv_obj_set_style_radius(ui->screen_wifi_btn_select, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ui->screen_wifi_btn_select, lv_color_hex(0x176edb), LV_PART_MAIN);

    lv_obj_update_layout(ui->screen_wifi);

    events_init_wifi_input_screen(ui);
}