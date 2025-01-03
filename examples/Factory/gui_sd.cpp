#include "lvgl.h"
#include <stdio.h>
#include "gui.h"
#include "event_init.h"
#include "Color.h"
#include "widgets_init.h"

void gui_SD_interface(lv_ui *ui)
{
    //Write codes screen_sd
    ui->screen_sd = lv_obj_create(NULL);
    // ui->g_kb_screen_sd = lv_zh_keyboard_create(ui->screen_sd, &lv_font_SourceHanSerifSC_Regular_18);
    // lv_obj_add_event_cb(ui->g_kb_screen_sd, kb_event_cb, LV_EVENT_ALL, NULL);
    // lv_obj_add_flag(ui->g_kb_screen_sd, LV_OBJ_FLAG_HIDDEN);
    // lv_obj_set_style_text_font(ui->g_kb_screen_sd, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_size(ui->screen_sd, 480, 222);
    lv_obj_set_scrollbar_mode(ui->screen_sd, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sd_label_background_1
    ui->screen_sd_label_background_1 = lv_label_create(ui->screen_sd);
    lv_label_set_text(ui->screen_sd_label_background_1, "");
    lv_label_set_long_mode(ui->screen_sd_label_background_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sd_label_background_1, 0, 0);
    lv_obj_set_size(ui->screen_sd_label_background_1, 480, 222);

    //Write style for screen_sd_label_background_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sd_label_background_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sd_label_background_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sd_label_background_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sd_label_background_1, lv_color_hex(0x00ffee), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sd_label_background_1, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen_sd_label_background_1, lv_color_hex(0xd000ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_main_stop(ui->screen_sd_label_background_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_grad_stop(ui->screen_sd_label_background_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    ui->srceen_sd_list =  lv_list_create(ui->screen_sd);
    lv_obj_set_pos(ui->srceen_sd_list, 5, 5);
    lv_obj_set_size(ui->srceen_sd_list, 470, 212);
    lv_obj_set_style_bg_opa(ui->srceen_sd_list, 120, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_fs_dir_open(&dir, "/sd");

}