#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "globals.h"

#include "/root/Desktop/test/lv_port_linux/src/api/account/account.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;
lv_obj_t *transaction_list;
// uint32_t active_theme_index = 0;

void formatAccountNumber(const char *input, char *output, size_t size) {
    int len = strlen(input);
    int j = 0;

    for (int i = 0; i < len && j < (int)size - 1; i++) {
        // Copy digit
        output[j++] = input[i];

        // Add space after every 4 digits (but not at the end)
        if ((i + 1) % 4 == 0 && i + 1 < len && j < (int)size - 1) {
            output[j++] = ' ';
        }
    }

    output[j] = '\0';
}

// static void cb_refresh_transaction_history(lv_event_t *e)
//{
    //if(accountNumber != NULL) {
        //display_transaction_history(userAccountNumber);
    //}
//}


void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // top bar cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
        {
            // main cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // welcome main text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.welcome_main_text = obj;
                    lv_obj_set_pos(obj, 0, -229);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Welcome to               !");
                }
                {
                    // welcome main text 2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.welcome_main_text_2 = obj;
                    lv_obj_set_pos(obj, 152, -229);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfff1b500), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "BankKo");
                }
                {
                    // tagline
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.tagline = obj;
                    lv_obj_set_pos(obj, 1, -208);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Your Bank, At Your Fingertips.");
                }
                {
                    // company name
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.company_name = obj;
                    lv_obj_set_pos(obj, 0, -186);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Group One Inc.");
                }
                {
                    // log in with text_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.log_in_with_text_2 = obj;
                    lv_obj_set_pos(obj, 267, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Are you a new user?");
                }
                {
                    // log in with text_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.log_in_with_text_3 = obj;
                    lv_obj_set_pos(obj, -305, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Log In With");
                }
                {
                    // log out button_2
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.log_out_button_2 = obj;
                    lv_obj_set_pos(obj, 1, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_fingerprint, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // transaction history text_6
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.transaction_history_text_6 = obj;
                            lv_obj_set_pos(obj, 15, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Fingerprint");
                        }
                        {
                            lv_obj_t *obj = lv_image_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 1);
                            lv_obj_set_size(obj, 29, 39);
                            lv_image_set_src(obj, &img_fingerprint_icon);
                            lv_image_set_scale(obj, 30);
                        }
                    }
                }
                {
                    // transaction history button_5
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.transaction_history_button_5 = obj;
                    lv_obj_set_pos(obj, 511, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // transaction history text_5
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.transaction_history_text_5 = obj;
                            lv_obj_set_pos(obj, 17, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);  // make it clickable
                            lv_obj_add_event_cb(obj, action_switch_to_register, LV_EVENT_PRESSED, (void *)0);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Register Now!");
                        }
                    }
                }
                {
                    // footing text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
    }

    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_fingerprint_scan() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.fingerprint_scan = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // top bar cont 2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 1
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_1 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf 1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_1 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
        {
            // fingerprint cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.fingerprint_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // input finger text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.input_finger_text = obj;
                    lv_obj_set_pos(obj, 0, -281);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please put your               \nin the scanner.");
                }
                {
                    // finger text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.finger_text = obj;
                    lv_obj_set_pos(obj, 107, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfff1b500), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Finger");
                }
                {
                    // fingerprint icon
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.fingerprint_icon = obj;
                    lv_obj_set_pos(obj, 298, 103);
                    lv_obj_set_size(obj, 121, 132);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);  // make it clickable
                    // lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_image_set_src(obj, &img_fingerprint_icon);
                    lv_image_set_scale(obj, 100);
                }
                {
                    // fs return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.fs_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // return text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.return_text = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // footing text 1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_1 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
    }

    tick_screen_fingerprint_scan();
}

void tick_screen_fingerprint_scan() {
}

void create_screen_pin() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.pin = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // top bar cont 3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 2
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_2 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf 2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_2 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
        {
            // main pin cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.main_pin_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // input pin text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.input_pin_text = obj;
                    lv_obj_set_pos(obj, -233, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please input        .");
                }
                {
                    // pin text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.pin_text = obj;
                    lv_obj_set_pos(obj, -143, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfff1b500), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "PIN");
                }
                {
                    // main pin tf 1
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.main_pin_tf_1 = obj;
                    lv_obj_set_pos(obj, 4, 76);
                    lv_obj_set_size(obj, 65, 65);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "0");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // main pin tf 2
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.main_pin_tf_2 = obj;
                    lv_obj_set_pos(obj, 85, 76);
                    lv_obj_set_size(obj, 65, 65);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "0");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // main pin tf 3
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.main_pin_tf_3 = obj;
                    lv_obj_set_pos(obj, 164, 76);
                    lv_obj_set_size(obj, 65, 65);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "0");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // main pin tf 4
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.main_pin_tf_4 = obj;
                    lv_obj_set_pos(obj, 242, 76);
                    lv_obj_set_size(obj, 65, 65);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "0");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // main pin return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.main_pin_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // transaction history text_7
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.transaction_history_text_7 = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    lv_obj_set_pos(obj, 359, 0);
                    lv_obj_set_size(obj, 358, 275);
                    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // footing text 2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_2 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
    }

    tick_screen_pin();
}

void tick_screen_pin() {
}

void create_screen_dashboard() {
    
 if (currentUser == NULL) {
        printf("[ERROR] currentUser is NULL in dashboard!\n");
        return;
    }

    lv_obj_clean(lv_scr_act());

    User *user = currentUser;
    // Copy account number
    strncpy(userAccountNumber, user->accountNumber, sizeof(userAccountNumber)-1);
    userAccountNumber[sizeof(userAccountNumber)-1] = '\0';

    // Format masked account
    char maskedAccount[32];
    char formattedAccount[32];
    formatAccountNumber(user->accountNumber, formattedAccount, sizeof(formattedAccount));

    int len = strlen(formattedAccount);
    if (len >= 4)
        snprintf(maskedAccount, sizeof(maskedAccount), "**** **** **** %.4s", formattedAccount + len - 4);
    else
        snprintf(maskedAccount, sizeof(maskedAccount), "****");

    // Extract first name (safe copy: DO NOT modify user->name)
    char tempName[64];
    strncpy(tempName, user->name, sizeof(tempName)-1);
    tempName[sizeof(tempName)-1] = '\0';

    char *spacePos = strchr(tempName, ' ');
    char firstName[32];

    if (spacePos != NULL) {
        size_t firstLen = spacePos - tempName;
        strncpy(firstName, tempName, firstLen);
        firstName[firstLen] = '\0';
    } else {
        strncpy(firstName, tempName, sizeof(firstName));
        firstName[sizeof(firstName)-1] = '\0';
    }

    // Get initial of last name
    char shortName[64];
    char *token = strtok(tempName, " ");
    char initial[4] = "";

    if (token) {
        strncpy(shortName, token, sizeof(shortName)-1);
        shortName[sizeof(shortName)-1] = '\0';
    }

    token = strtok(NULL, " ");
    if (token && strlen(token) > 0) {
        snprintf(initial, sizeof(initial), " %c.", token[0]);
        strncat(shortName, initial, sizeof(shortName)-strlen(shortName)-1);
    }

    // Greeting
    char greetingText[64];
    snprintf(greetingText, sizeof(greetingText), "Hello, %s!", firstName);

    // Balance
    char balanceText[64];
    snprintf(balanceText, sizeof(balanceText), "Php %.2f", user->balance);

        lv_obj_t *obj = lv_obj_create(NULL);
        objects.dashboard = obj;
	lv_scr_load(obj);
        lv_obj_set_pos(obj, 0, 0);
        lv_obj_set_size(obj, 800, 480);
        lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_margin_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_image_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
        {
        lv_obj_t *parent_obj = obj;
        {
            // dashboard greeting
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dashboard_greeting = obj;
            lv_obj_set_pos(obj, 261, 89);
            lv_obj_set_size(obj, 278, 110);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // welcome text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.welcome_text = obj;
                    lv_obj_set_pos(obj, 0, -76);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Welcome to BankKo!");
                }
                {
                    // hello user tf
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.hello_user_tf = obj;
                    lv_obj_set_pos(obj, 0, -40);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(objects.hello_user_tf, greetingText);
                }
                {
                    // greeting text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.greeting_text = obj;
                    lv_obj_set_pos(obj, 0, -13);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "How can we help you today?");
                }
            }
        }
        {
            // dashboard cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dashboard_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // balance button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.balance_button = obj;
                    lv_obj_set_pos(obj, 1, 0);
                    lv_obj_set_size(obj, 219, 110);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // balance text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.balance_text = obj;
                            lv_obj_set_pos(obj, -32, -31);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Your balance");
                        }
                        {
                            // balance display
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.balance_tf = obj;
                            lv_obj_set_pos(obj, -2, 45);
                            lv_obj_set_size(obj, 182, 30);
                            lv_label_set_text(obj, balanceText);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                        }

                    }
                }
                {
                    // money transfer button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.money_transfer_button = obj;
                    lv_obj_set_pos(obj, 0, 125);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_money_transfer, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // money transfer main text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.money_transfer_main_text = obj;
                            lv_obj_set_pos(obj, -18, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Money Transfer");
                        }
                    }
                }
                {
                    // Cash deposit button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cash_deposit_button = obj;
                    lv_obj_set_pos(obj, 0, 200);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_cash_deposit, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cash deposit text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cash_deposit_text = obj;
                            lv_obj_set_pos(obj, -27, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Cash Deposit");
                        }
                    }
                }
                {
                    // transaction history button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.transaction_history_button = obj;
                    lv_obj_set_pos(obj, 0, 274);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_transac_his, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // transaction history text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.transaction_history_text = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Transaction History");
                        }
                    }
                }
                {
                    // card details button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.card_details_button = obj;
                    lv_obj_set_pos(obj, 242, 125);
                    lv_obj_set_size(obj, 234, 147);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // account number tf
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.account_number_tf = obj;
                            lv_obj_set_pos(obj, -15, -41);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_20, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(objects.account_number_tf, maskedAccount);
                        }
                        {
                            // card name tf
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.card_name_tf = obj;
                            lv_obj_set_pos(obj, -59, -17);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "GoTyme Bank");
                        }
                        {
                            // expiry tf
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.expiry_tf = obj;
                            lv_obj_set_pos(obj, 77, 19);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "** / **");
                        }
                        {
                            // card acc tf
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.card_acc_tf = obj;
                            lv_obj_set_pos(obj, -72, 25);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, shortName);
                        }
                        {
                            // tap to change text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.tap_to_change_text = obj;
                            lv_obj_set_pos(obj, 40, 58);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Tap to Change Card");
                        }
                    }
                }
                {
                    // edit profile button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.edit_profile_button = obj;
                    lv_obj_set_pos(obj, 498, 25);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // edit profile text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.edit_profile_text = obj;
                            lv_obj_set_pos(obj, 35, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Edit Profile");
                        }
                    }
                }
                {
                    // change pin button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.change_pin_button = obj;
                    lv_obj_set_pos(obj, 498, 99);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // change pin text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.change_pin_text = obj;
                            lv_obj_set_pos(obj, 43, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Add Card");
                        }
                    }
                }
                {
                    // customer service button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.customer_service_button = obj;
                    lv_obj_set_pos(obj, 498, 174);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // customer text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.customer_text = obj;
                            lv_obj_set_pos(obj, 6, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Customer Service");
                        }
                    }
                }
                {
                    // log out button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.log_out_button = obj;
                    lv_obj_set_pos(obj, 498, 249);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // logout text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.logout_text = obj;
                            lv_obj_set_pos(obj, 51, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Log out");
                        }
                    }
                }
                {
                    // footing text 3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_3 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
        {
            // top bar cont 4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_4 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 3
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_3 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_3 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_dashboard();
}

void tick_screen_dashboard() {
}

void create_screen_money_transfer() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.money_transfer = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // MT cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mt_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Money Transfer text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.money_transfer_text = obj;
                    lv_obj_set_pos(obj, -245, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Money Transfer");
                }
                {
                    // partner banks text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.partner_banks_text = obj;
                    lv_obj_set_pos(obj, -300, -279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Partner Banks");
                }
                {
                    // bank button
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.bank_button = obj;
                    lv_obj_set_pos(obj, 30, 97);
                    lv_obj_set_size(obj, 658, 240);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_add_event_cb(obj, action_switch_to_mt_amount, LV_EVENT_PRESSED, (void *)0);
                    lv_image_set_src(obj, &img_bank_logo);
                    lv_image_set_scale(obj, 90);
                }
                {
                    // MT return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.mt_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // MT return text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mt_return_text = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // footing text 4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_4 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
        {
            // top bar cont 5
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_5 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 4
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_4 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_4 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_money_transfer();
}

void tick_screen_money_transfer() {
}

void create_screen_mt_account_num() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.mt_account_num = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // mt aaccount cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mt_aaccount_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Money Transfer text_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.money_transfer_text_2 = obj;
                    lv_obj_set_pos(obj, -245, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Money Transfer");
                }
                {
                    // account number text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.account_number_text = obj;
                    lv_obj_set_pos(obj, -220, -279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please enter the account number.");
                }
                {
                    // MT amount tf_1
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.mt_amount_tf_1 = obj;
                    lv_obj_set_pos(obj, 0, 99);
                    lv_obj_set_size(obj, 325, 70);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "00000000");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_max_length(obj, 16);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // MT return button_2
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.mt_return_button_2 = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_money_transfer, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // MT return text 2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mt_return_text_2 = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // footing text 6
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_6 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
                {
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    lv_obj_set_pos(obj, 360, 0);
                    lv_obj_set_size(obj, 358, 275);
                    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_keyboard_set_textarea(obj, objects.mt_amount_tf_1);
                    lv_obj_add_event_cb(obj, keyboard_print_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
                    lv_obj_add_event_cb(obj, keyboard_ready_event_cb_1, LV_EVENT_READY, NULL);
                }
            }
        }
        {
            // top bar cont 6_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_6_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 6
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_6 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_6
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_6 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_mt_account_num();
}

void tick_screen_mt_account_num() {
}

void create_screen_mt_amount() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.mt_amount = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // mt amount cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mt_amount_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Money Transfer text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.money_transfer_text_1 = obj;
                    lv_obj_set_pos(obj, -245, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Money Transfer");
                }
                {
                    // amount to transfer text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.amount_to_transfer_text = obj;
                    lv_obj_set_pos(obj, -227, -279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please input amount to transfer.");
                }
                {
                    // php text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.php_text = obj;
                    lv_obj_set_pos(obj, -320, -182);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Php");
                }
                {
                    // MT amount tf
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.mt_amount_tf = obj;
                    lv_obj_set_pos(obj, 90, 99);
                    lv_obj_set_size(obj, 235, 70);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "000 000 000");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // MT return button_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.mt_return_button_1 = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_money_transfer, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // MT return text 1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mt_return_text_1 = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // footing text 5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_5 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
                {
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    lv_obj_set_pos(obj, 360, 0);
                    lv_obj_set_size(obj, 358, 275);
                    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_keyboard_set_textarea(obj, objects.mt_amount_tf);
                    lv_obj_add_event_cb(obj, keyboard_print_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
                    lv_obj_add_event_cb(obj, keyboard_ready_event_cb, LV_EVENT_READY, NULL);
                }
            }
        }
        {
            // top bar cont 6
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_6 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 5
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_5 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_5 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_mt_amount();
}

void tick_screen_mt_amount() {
}

void create_screen_mt_pin_confirmation() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.mt_pin_confirmation = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // dash board buttons_7
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.dash_board_buttons_7 = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // mt pin cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.mt_pin_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Money Transfer text_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.money_transfer_text_3 = obj;
                    lv_obj_set_pos(obj, -245, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Money Transfer");
                }
                {
                    // enter pin text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.enter_pin_text = obj;
                    lv_obj_set_pos(obj, -290, -279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please enter PIN.");
                }

                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.mt_pin_tf_1 = obj;
                    lv_obj_set_pos(obj, 0, 99);
                    lv_obj_set_size(obj, 325, 70);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "000 000 000");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_max_length(obj, 4);
                    lv_textarea_set_password_mode(obj, true);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    lv_obj_t *obj = lv_keyboard_create(parent_obj);
                    lv_obj_set_pos(obj, 401, 88);
                    lv_obj_set_size(obj, 358, 275);
                    lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
                    lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_keyboard_set_textarea(obj, objects.mt_pin_tf_1);
                    lv_obj_add_event_cb(obj, keyboard_print_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
                    lv_obj_add_event_cb(obj, keyboard_ready_event_cb_2, LV_EVENT_READY, NULL);
                }
                {
                    // footing text 7
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_7 = obj;
                    lv_obj_set_pos(obj, 0, 162);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
                {
                    // mt return button 3
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.mt_return_button_3 = obj;
                    lv_obj_set_pos(obj, 40, 364);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_amount, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // mt return text 3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.mt_return_text_3 = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
            }
        {
            // top bar cont 8
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_8 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 7
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_7 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_7
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_7 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_mt_pin_confirmation();
}

void tick_screen_mt_pin_confirmation() {
}

void create_screen_bank_transfer_complete() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bank_transfer_complete = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // bt complete cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.bt_complete_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // bt comp text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.bt_comp_text = obj;
                    lv_obj_set_pos(obj, -5, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Bank Transfer Complete!");
                }
                {
                    // bt return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.bt_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // bt return text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.bt_return_text = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // print button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.print_button = obj;
                    lv_obj_set_pos(obj, 498, 275);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_add_event_cb(obj, print_receipt_event_cb, LV_EVENT_CLICKED, NULL);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // print text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.print_text = obj;
                            lv_obj_set_pos(obj, 30, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Print receipt");
                        }
                    }
                }
                {
                    // footing text 8
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_8 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
                {
                    // === Outer container (acts like outer <div>) ===
                    lv_obj_t *outer_cont = lv_obj_create(parent_obj);
                    lv_obj_set_size(outer_cont, 354, 208);
                    lv_obj_set_pos(outer_cont, 182, 47);
                    lv_obj_set_scrollbar_mode(outer_cont, LV_SCROLLBAR_MODE_AUTO);
                    lv_obj_set_style_bg_color(outer_cont, lv_color_hex(0xFFFFFF), 0);
                    lv_obj_set_style_bg_opa(outer_cont, LV_OPA_COVER, 0);
                    lv_obj_set_style_border_width(outer_cont, 0, 0);
                    lv_obj_set_style_radius(outer_cont, 5, 0);

                    // === Inner container (acts like inner <div>) ===
                    lv_obj_t *inner_cont = lv_obj_create(outer_cont);
                    lv_obj_set_width(inner_cont, lv_pct(90)); // slightly smaller than outer
                    lv_obj_set_height(inner_cont, LV_SIZE_CONTENT);
                    lv_obj_center(inner_cont);
                    lv_obj_set_pos(inner_cont, 23, 0);
                    lv_obj_set_style_bg_opa(inner_cont, LV_OPA_TRANSP, 0);
                    lv_obj_set_style_border_width(inner_cont, 0, 0);
                    lv_obj_set_style_pad_all(inner_cont, 0, 0);

                    // === Label (text inside the inner div) ===
                    lv_obj_t *receipt_label = lv_label_create(inner_cont);
                    lv_obj_set_width(receipt_label, lv_pct(100));
                    lv_label_set_long_mode(receipt_label, LV_LABEL_LONG_WRAP);
                    lv_obj_set_style_text_align(receipt_label, LV_TEXT_ALIGN_LEFT, 0);
                    lv_obj_set_style_text_font(receipt_label, &lv_font_montserrat_12, 0);
                    lv_obj_set_style_text_color(receipt_label, lv_color_hex(0x000000), 0);
                    lv_obj_set_style_pad_all(receipt_label, 8, 0);

                    // === Get current date and time ===
                    setenv("TZ", "Asia/Manila", 1); // overwrite any existing TZ
                    tzset(); // apply

                    time_t now = time(NULL);
                    struct tm tm_buf;
                    struct tm *t = NULL;

                    /* Use thread-safe localtime_r if available */

                    #if defined(_POSIX_THREAD_SAFE_FUNCTIONS) || defined(_BSD_SOURCE) || defined(_GNU_SOURCE)
                    localtime_r(&now, &tm_buf);
                    t = &tm_buf;

                    #else
                    t = localtime(&now);
                    #endif

                    char date_str[32];
                    char time_str[32];
                    if (t) {
                       snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d",
                                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
                       snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
                                t->tm_hour, t->tm_min, t->tm_sec);
                    } else {
                       strcpy(date_str, "??/??/????");
                       strcpy(time_str, "??:??:??");
                    }

                    const int RIGHT_COLUMN_WIDTH = 20; // adjust this to match your receipt width

                    const char *receipt_text =
                        "                     GROUP ONE INC.\n"
                        "                            BANKKO\n"
                        "--------------------------------------------\n"
                        "Transaction Type:          Money Transfer\n"
                        "Account No. (To):       %*s\n"
                        "\n"
                        "Amount Sent:               %*s\n"
                        "--------------------------------------------\n"
                        "Date:                                 %*s\n"
                        "Time:                                    %*s\n"
                        "\n\n"
                        "       Thank you for banking with us.\n";

                    char formatted_receipt[512];
                    char amount_with_currency[32];
                    snprintf(amount_with_currency, sizeof(amount_with_currency), "Php %s", amount);

                    snprintf(formatted_receipt, sizeof(formatted_receipt),
                             receipt_text,
                             RIGHT_COLUMN_WIDTH, accountNumber,
                             RIGHT_COLUMN_WIDTH, amount_with_currency,
                             RIGHT_COLUMN_WIDTH, date_str,
                             RIGHT_COLUMN_WIDTH, time_str
                    );

                    lv_label_set_text(receipt_label, formatted_receipt);
                }

            }
        }
        {
            // top bar cont 9
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_9 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 8
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_8 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_8
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_8 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_bank_transfer_complete();
}

void tick_screen_bank_transfer_complete() {
}

void create_screen_cash_deposit() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.cash_deposit = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // cd cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cd_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // cash deposit text 1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cash_deposit_text_1 = obj;
                    lv_obj_set_pos(obj, -263, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Cash Deposit");
                }
                {
                    // amount to transfer text_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.amount_to_transfer_text_1 = obj;
                    lv_obj_set_pos(obj, -227, -279);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please input amount to transfer.");
                }
                {
                    // php text 1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.php_text_1 = obj;
                    lv_obj_set_pos(obj, -320, -182);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Php");
                }
                {
                    // cd amount tf
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.cd_amount_tf = obj;
                    lv_obj_set_pos(obj, 90, 99);
                    lv_obj_set_size(obj, 235, 70);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "000 000 000");
                    lv_textarea_set_one_line(obj, false);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // CD return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cd_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // CD return text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cd_return_text = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // footing text 9
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_9 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
        {
            // top bar cont 6_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_6_2 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 9
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_9 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_9
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_9 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_cash_deposit();
}

void tick_screen_cash_deposit() {
}

void create_screen_cash_deposit_complete() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.cash_deposit_complete = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // cd success cont
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.cd_success_cont = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Cash deposit success text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.cash_deposit_success_text = obj;
                    lv_obj_set_pos(obj, 0, -309);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_28, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Cash Deposit Success!");
                }
                {
                    // cd return button 1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.cd_return_button_1 = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // cd return return button 1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.cd_return_return_button_1 = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
                {
                    // print button_1
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.print_button_1 = obj;
                    lv_obj_set_pos(obj, 498, 275);
                    lv_obj_set_size(obj, 220, 62);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff4444), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_stop(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // print text_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.print_text_1 = obj;
                            lv_obj_set_pos(obj, 30, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Print receipt");
                        }
                    }
                }
                {
                    // footing text 10
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_10 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
                {
                    // cd table
                    lv_obj_t *obj = lv_table_create(parent_obj);
                    objects.cd_table = obj;
                    lv_obj_set_pos(obj, 182, 47);
                    lv_obj_set_size(obj, 354, 208);
                }
            }
        }
        {
            // top bar cont 9_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_9_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 10
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_10 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf 10
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_10 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_cash_deposit_complete();
}

void tick_screen_cash_deposit_complete() {
}

void create_screen_transaction_history() {

    if (currentUser == NULL) {
        printf("[ERROR] currentUser is NULL in dashboard!\n");
        return;
    }

    // lv_obj_clean(lv_scr_act());

    lv_obj_t *obj = lv_obj_create(NULL);
    objects.transaction_history = obj;

    lv_scr_load(obj);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    {
        lv_obj_t *parent_obj = obj;

        {
            // transac history cont
            {
                lv_obj_t *parent_obj = obj;

		{
		// Create the table
		lv_obj_t *table = lv_table_create(parent_obj);
		transaction_list = table;

		lv_obj_set_size(table, 718, 210);
		lv_obj_set_pos(table, 40, 60);

		// Make table background transparent
		lv_obj_set_style_bg_opa(table, LV_OPA_TRANSP, LV_PART_MAIN);
		lv_obj_set_style_border_color(table, lv_color_white(), LV_PART_MAIN);
		lv_obj_set_style_border_width(table, 2, LV_PART_MAIN);
		lv_obj_set_style_radius(table, 5, LV_PART_MAIN);

		// Make all cells transparent and text white
		lv_obj_set_style_bg_opa(table, LV_OPA_TRANSP, LV_PART_ITEMS);
		lv_obj_set_style_text_color(table, lv_color_white(), LV_PART_ITEMS);
		lv_obj_set_style_text_align(table, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS);

		// Define table dimensions
		lv_table_set_col_cnt(table, 4);
		lv_table_set_row_cnt(table, 5); // 1 header + 4 filler rows
		
		int count = 0;
		User *user = currentUser;
		printf("accountNumber: ", accountNumber);
		Transaction* txs = fetch_transaction_history(accountNumber, &count);

		if (txs != NULL && count > 0) {
		    // Set table row count: 1 for header + number of transactions
		    lv_table_set_row_cnt(table, count + 1);

		    // Column headers
		    const char* headers[] = {"ID", "Type", "Amount", "Date"};
		    for(int c = 0; c < 4; c++) {
			lv_table_set_cell_value(table, 0, c, headers[c]);
		    }

		    char buf[32];
		    for(int r = 0; r < count; r++) {
			// ID
			snprintf(buf, sizeof(buf), "%d", txs[r].id);
			lv_table_set_cell_value(table, r + 1, 0, buf);

			// Type
			lv_table_set_cell_value(table, r + 1, 1, txs[r].type);

			// Amount
			snprintf(buf, sizeof(buf), "%.2f", txs[r].amount);
			lv_table_set_cell_value(table, r + 1, 2, buf);

			// Date
			lv_table_set_cell_value(table, r + 1, 3, txs[r].date);
		    }

		    free(txs);
		} else {
		    printf("No transactions found.\n");
		    // Optionally, clear table or show placeholder row
		    lv_table_set_row_cnt(table, 1);
		    const char* headers[] = {"ID", "Type", "Amount", "Date"};
		    for(int c = 0; c < 4; c++) {
			lv_table_set_cell_value(table, 0, c, headers[c]);
		    }
		}
		}
                { // footing text 11
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_11 = obj;
                    lv_obj_set_pos(obj, 0, 145);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }

                { // transac history return button
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.transac_history_return_button = obj;
                    lv_obj_set_pos(obj, 0, 275);
                    lv_obj_set_size(obj, 207, 62);
                    lv_obj_add_event_cb(obj, action_switch_to_dashboard, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_margin_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_outline_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                    {
                        lv_obj_t *parent_obj = obj;

                        { // transac history return text
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.transac_history_return_text = obj;
                            lv_obj_set_pos(obj, -47, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Return");
                        }
                    }
                }
            }
        }
    }

    // Top bar
    lv_obj_t *parent_obj = obj;

    { // top bar cont 12
        lv_obj_t *obj = lv_obj_create(parent_obj);
        objects.top_bar_cont_12 = obj;
        lv_obj_set_pos(obj, 0, 0);
        lv_obj_set_size(obj, 800, 50);
        lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

        {
            lv_obj_t *parent_obj = obj;

            { // banko logo 11
                lv_obj_t *obj = lv_image_create(parent_obj);
                objects.banko_logo_11 = obj;
                lv_obj_set_pos(obj, 34, 6);
                lv_obj_set_size(obj, 87, 39);
                lv_image_set_src(obj, &img_ban_ko_logo);
                lv_image_set_scale(obj, 30);
            }

            { // time label tf_11
                lv_obj_t *obj = lv_label_create(parent_obj);
                objects.time_label_tf_11 = obj;
                lv_obj_set_pos(obj, 735, 16);
                lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(obj, "00:00");
            }
        }
    }

    // ✅ Add screen load event to refresh transaction history every time screen is shown
    //lv_obj_add_event_cb(objects.transaction_history, cb_refresh_transaction_history, LV_EVENT_SCREEN_LOAD_START, NULL);
    tick_screen_transaction_history();
}

void tick_screen_transaction_history() {
}

void create_screen_personal_info_registration() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.personal_info_registration = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff92154b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff0e2d76), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(obj, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_image_src(obj, &img_bckg, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // register tfs
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.register_tfs = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 337);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // footing text 12
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.footing_text_12 = obj;
                    lv_obj_set_pos(obj, -264, 157);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "For your query, please contact:\n(02) 123 456 7890");
                }
            }
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            lv_obj_set_pos(obj, 254, 253);
            lv_obj_set_size(obj, 481, 173);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 41, 89);
            lv_obj_set_size(obj, 718, 300);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Personal Information
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information = obj;
                    lv_obj_set_pos(obj, -276, -126);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_bold_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xfff1b500), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Personal Information");
                }
                {
                    // Personal Information_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information_1 = obj;
                    lv_obj_set_pos(obj, -281, -94);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "What is your name?");
                }
                {
                    // Last name_1
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.last_name_1 = obj;
                    lv_obj_set_pos(obj, 17, 70);
                    lv_obj_set_size(obj, 173, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "Last Name");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Firs_3
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.firs_3 = obj;
                    lv_obj_set_pos(obj, 17, 117);
                    lv_obj_set_size(obj, 173, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "First Name");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Firs_4
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.firs_4 = obj;
                    lv_obj_set_pos(obj, 17, 165);
                    lv_obj_set_size(obj, 173, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "Middle Name (optional)");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Personal Information_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information_2 = obj;
                    lv_obj_set_pos(obj, -289, 76);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "What is your sex?");
                }
                {
                    lv_obj_t *obj = lv_dropdown_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 17, 242);
                    lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
                    lv_dropdown_set_options(obj, "Tap to Select\nMale\nFemale");
                    lv_dropdown_set_selected(obj, 0);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Personal Information_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information_3 = obj;
                    lv_obj_set_pos(obj, -72, -126);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "When is your birth year?");
                }
                {
                    // Last name_2
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.last_name_2 = obj;
                    lv_obj_set_pos(obj, 213, 38);
                    lv_obj_set_size(obj, 146, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "Year");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Personal Information_5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information_5 = obj;
                    lv_obj_set_pos(obj, 128, -126);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please input your e-mail address");
                }
                {
                    // Last name_4
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.last_name_4 = obj;
                    lv_obj_set_pos(obj, 388, 38);
                    lv_obj_set_size(obj, 177, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "E-mail address");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // Personal Information_6
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.personal_information_6 = obj;
                    lv_obj_set_pos(obj, -25, -53);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Please input your current home address");
                }
                {
                    // Last name_5
                    lv_obj_t *obj = lv_textarea_create(parent_obj);
                    objects.last_name_5 = obj;
                    lv_obj_set_pos(obj, 213, 108);
                    lv_obj_set_size(obj, 480, 38);
                    lv_textarea_set_max_length(obj, 128);
                    lv_textarea_set_placeholder_text(obj, "Unit/Floor, Bldg./Street/Subd., City, Province, Postal code");
                    lv_textarea_set_one_line(obj, true);
                    lv_textarea_set_password_mode(obj, false);
                    lv_obj_set_style_text_font(obj, &ui_font_montserrat_italic_12, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // top bar cont 13
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.top_bar_cont_13 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 50);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // banko logo 12
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.banko_logo_12 = obj;
                    lv_obj_set_pos(obj, 34, 6);
                    lv_obj_set_size(obj, 87, 39);
                    lv_image_set_src(obj, &img_ban_ko_logo);
                    lv_image_set_scale(obj, 30);
                }
                {
                    // time label tf_12
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.time_label_tf_12 = obj;
                    lv_obj_set_pos(obj, 735, 16);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "00:00");
                }
            }
        }
    }

    tick_screen_personal_info_registration();
}

void tick_screen_personal_info_registration() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_fingerprint_scan,
    tick_screen_pin,
    tick_screen_dashboard,
    tick_screen_money_transfer,
    tick_screen_mt_account_num,
    tick_screen_mt_amount,
    tick_screen_mt_pin_confirmation,
    tick_screen_bank_transfer_complete,
    tick_screen_cash_deposit,
    tick_screen_cash_deposit_complete,
    tick_screen_transaction_history,
    tick_screen_personal_info_registration,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    create_screen_main();
    create_screen_fingerprint_scan();
    create_screen_pin();
    create_screen_dashboard();
    create_screen_money_transfer();
    create_screen_mt_account_num();
    create_screen_mt_amount();
    create_screen_mt_pin_confirmation();
    // create_screen_bank_transfer_complete();
    create_screen_cash_deposit();
    create_screen_cash_deposit_complete();
    // create_screen_transaction_history();
    create_screen_personal_info_registration();
}
