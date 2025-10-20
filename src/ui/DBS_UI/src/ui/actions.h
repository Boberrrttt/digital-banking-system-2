#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <lvgl/lvgl.h>
#include <stdlib.h>
#include "ui.h"
#include "screens.h"
#include "globals.h"
#include "receipt.h"

/* ===== Screen switch functions ===== */
extern void action_switch_to_fingerprint(lv_event_t * e);
extern void action_switch_to_pin(lv_event_t * e);
extern void action_switch_to_main(lv_event_t * e);
extern void action_switch_to_dashboard(lv_event_t * e);
extern void action_switch_to_money_transfer(lv_event_t * e);
extern void action_switch_to_cash_deposit(lv_event_t * e);
extern void action_switch_to_transac_his(lv_event_t * e);
extern void action_switch_to_account_num(lv_event_t * e);
extern void action_switch_to_amount(lv_event_t * e);
extern void action_switch_to_bank_transfer_complete(lv_event_t * e);
extern void action_switch_to_register(lv_event_t * e);
extern void action_switch_to_mt_amount(lv_event_t * e);
extern void action_switch_to_mt_account_num(lv_event_t * e);
extern void action_switch_to_mt_pin_confirmation(lv_event_t * e);

/* ===== Keyboard callbacks ===== */
extern void keyboard_print_event_cb(lv_event_t * e);
extern void keyboard_ready_event_cb(lv_event_t * e);
extern void keyboard_ready_event_cb_1(lv_event_t * e);
extern void keyboard_ready_event_cb_2(lv_event_t * e);

/* ===== Other functions ===== */
extern void print_receipt_event_cb(lv_event_t * e);
extern void update_time_cb(lv_timer_t *timer);

#endif /* ACTIONS_H */

