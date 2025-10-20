#include <stdio.h>
#include <string.h>
#include <time.h>
#include <lvgl/lvgl.h>
#include <stdlib.h>
#include "ui.h"
#include "screens.h"
#include "globals.h"
#include "receipt.h"

void action_switch_to_fingerprint(lv_event_t * e) {
    printf("Switch to fingerprint screen\n");
    lv_scr_load(objects.fingerprint_scan);
}

void action_switch_to_pin(lv_event_t * e) {
    printf("Switch to pin screen\n");
    lv_scr_load(objects.pin);
}

void action_switch_to_main(lv_event_t * e) {
    printf("Switch to main screen\n");
    lv_scr_load(objects.main);
}

void action_switch_to_dashboard(lv_event_t * e) {
    printf("Switch to dashboard screen\n");
    lv_scr_load(objects.dashboard);
}

void action_switch_to_money_transfer(lv_event_t * e) {
    printf("Switch to money transfer screen\n");
    lv_scr_load(objects.money_transfer);
}

void action_switch_to_cash_deposit(lv_event_t * e) {
    printf("Switch to cash deposit screen\n");
    lv_scr_load(objects.cash_deposit);
}

void action_switch_to_transac_his(lv_event_t * e) {
    printf("Switch to transaction history screen\n");
    lv_scr_load(objects.transaction_history);
}

void action_switch_to_account_num(lv_event_t * e) {
    printf("Switch to account number screen\n");
}

void action_switch_to_amount(lv_event_t * e) {
    printf("Switch to amount screen\n");
}

void action_switch_to_bank_transfer_complete(lv_event_t * e) {
    printf("Switch to bank transfer complete\n");
    lv_scr_load(objects.bank_transfer_complete);
}

void action_switch_to_register(lv_event_t * e) {
    printf("Switch to registration\n");
    lv_scr_load(objects.personal_info_registration);
}

void action_switch_to_mt_amount(lv_event_t * e) {
    printf("Switch to money transfer amount\n");
    lv_scr_load(objects.mt_amount);
}

void action_switch_to_mt_account_num(lv_event_t * e) {
    printf("Switch to money transfer account num\n");
    lv_scr_load(objects.mt_account_num);
}

void action_switch_to_mt_pin_confirmation(lv_event_t * e) {
    printf("Switch to money transfer pin confirmation\n");
    lv_scr_load(objects.mt_pin_confirmation);
}


void keyboard_print_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_VALUE_CHANGED) return;

    lv_obj_t * kb = lv_event_get_target_obj(e);
    lv_obj_t * ta = lv_keyboard_get_textarea(kb);
    const char * txt = lv_textarea_get_text(ta);

    printf("Current text: %s\n", txt);
    fflush(stdout);
}

void keyboard_ready_event_cb(lv_event_t * e) {
    printf("Enter/OK pressed!\n");

    lv_obj_t * kb = lv_event_get_target(e);

    lv_obj_t * ta = lv_keyboard_get_textarea(kb);

    if (ta != NULL) {
        const char * txt = lv_textarea_get_text(ta);

        strncpy(amount, txt, sizeof(amount) - 1);
        amount[sizeof(amount) - 1] = '\0';
        fflush(stdout);
    } else {
        printf("[Error] No linked textarea found!\n");
    }

    lv_textarea_set_text(ta, "");
    action_switch_to_mt_account_num(e);
}

void keyboard_ready_event_cb_1(lv_event_t * e) {
    printf("Enter/OK pressed!\n");

    lv_obj_t * kb = lv_event_get_target(e);

    lv_obj_t * ta = lv_keyboard_get_textarea(kb);

    if (ta != NULL) {
        const char * txt = lv_textarea_get_text(ta);

        strncpy(accountNumber, txt, sizeof(accountNumber) - 1);
        accountNumber[sizeof(accountNumber) - 1] = '\0';
        fflush(stdout);
    } else {
        printf("[Error] No linked textarea found!\n");
    }

    lv_textarea_set_text(ta, "");
    action_switch_to_mt_pin_confirmation(e);
}

void keyboard_ready_event_cb_2(lv_event_t * e) {
    printf("Enter/OK pressed!\n");

    lv_obj_t * kb = lv_event_get_target(e);

    lv_obj_t * ta = lv_keyboard_get_textarea(kb);

    if (ta != NULL) {
        const char * txt = lv_textarea_get_text(ta);

        strncpy(pin, txt, sizeof(pin) - 1);
        pin[sizeof(pin) - 1] = '\0';
        fflush(stdout);
    } else {
        printf("[Error] No linked textarea found!\n");
    }

    lv_textarea_set_text(ta, "");
    create_screen_bank_transfer_complete();
    action_switch_to_bank_transfer_complete(e);
}

void print_receipt_event_cb(lv_event_t * e) {
    print_receipt(accountNumber, amount, "Money Transfer");
}

void update_time_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);

    time_t now;
    struct tm *tm_info;
    static char time_str[9];

    setenv("TZ", "Asia/Manila", 1);
    tzset();

    time(&now);
    tm_info = localtime(&now);

    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);

    lv_obj_t *time_labels[] = {
        objects.time_label_tf,
        objects.time_label_tf_1,
        objects.time_label_tf_2,
        objects.time_label_tf_3,
        objects.time_label_tf_4,
        objects.time_label_tf_5,
        objects.time_label_tf_6,
        objects.time_label_tf_7,
        objects.time_label_tf_8,
        objects.time_label_tf_9,
        objects.time_label_tf_10,
        objects.time_label_tf_11,
        objects.time_label_tf_12
    };

    for (int i = 0; i < 13; i++) {
        if (time_labels[i]) {
            lv_label_set_text(time_labels[i], time_str);
        }
    }
}
