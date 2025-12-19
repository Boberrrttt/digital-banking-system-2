#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *fingerprint_scan;
    lv_obj_t *pin;
    lv_obj_t *dashboard;
    lv_obj_t *money_transfer;
    lv_obj_t *mt_account_num;
    lv_obj_t *mt_amount;
    lv_obj_t *mt_pin_confirmation;
    lv_obj_t *bank_transfer_complete;
    lv_obj_t *cash_deposit;
    lv_obj_t *cash_deposit_complete;
    lv_obj_t *transaction_history;
    lv_obj_t *personal_info_registration;
    lv_obj_t *top_bar_cont;
    lv_obj_t *banko_logo;
    lv_obj_t *time_label_tf;
    lv_obj_t *main_cont;
    lv_obj_t *welcome_main_text;
    lv_obj_t *welcome_main_text_2;
    lv_obj_t *tagline;
    lv_obj_t *company_name;
    lv_obj_t *log_in_with_text_2;
    lv_obj_t *log_in_with_text_3;
    lv_obj_t *log_out_button_2;
    lv_obj_t *transaction_history_text_6;
    lv_obj_t *transaction_history_button_5;
    lv_obj_t *transaction_history_text_5;
    lv_obj_t *footing_text;
    lv_obj_t *top_bar_cont_2;
    lv_obj_t *banko_logo_1;
    lv_obj_t *time_label_tf_1;
    lv_obj_t *fingerprint_cont;
    lv_obj_t *input_finger_text;
    lv_obj_t *finger_text;
    lv_obj_t *fingerprint_icon;
    lv_obj_t *fs_return_button;
    lv_obj_t *return_text;
    lv_obj_t *footing_text_1;
    lv_obj_t *top_bar_cont_3;
    lv_obj_t *banko_logo_2;
    lv_obj_t *time_label_tf_2;
    lv_obj_t *main_pin_cont;
    lv_obj_t *input_pin_text;
    lv_obj_t *pin_text;
    lv_obj_t *main_pin_tf_1;
    lv_obj_t *main_pin_tf_2;
    lv_obj_t *main_pin_tf_3;
    lv_obj_t *main_pin_tf_4;
    lv_obj_t *main_pin_return_button;
    lv_obj_t *transaction_history_text_7;
    lv_obj_t *footing_text_2;
    lv_obj_t *dashboard_greeting;
    lv_obj_t *welcome_text;
    lv_obj_t *hello_user_tf;
    lv_obj_t *greeting_text;
    lv_obj_t *dashboard_cont;
    lv_obj_t *balance_button;
    lv_obj_t *balance_text;
    lv_obj_t *balance_tf;
    lv_obj_t *money_transfer_button;
    lv_obj_t *money_transfer_main_text;
    lv_obj_t *cash_deposit_button;
    lv_obj_t *cash_deposit_text;
    lv_obj_t *transaction_history_button;
    lv_obj_t *transaction_history_text;
    lv_obj_t *card_details_button;
    lv_obj_t *account_number_tf;
    lv_obj_t *card_name_tf;
    lv_obj_t *expiry_tf;
    lv_obj_t *card_acc_tf;
    lv_obj_t *tap_to_change_text;
    lv_obj_t *edit_profile_button;
    lv_obj_t *edit_profile_text;
    lv_obj_t *change_pin_button;
    lv_obj_t *change_pin_text;
    lv_obj_t *customer_service_button;
    lv_obj_t *customer_text;
    lv_obj_t *log_out_button;
    lv_obj_t *logout_text;
    lv_obj_t *footing_text_3;
    lv_obj_t *top_bar_cont_4;
    lv_obj_t *banko_logo_3;
    lv_obj_t *time_label_tf_3;
    lv_obj_t *mt_cont;
    lv_obj_t *money_transfer_text;
    lv_obj_t *partner_banks_text;
    lv_obj_t *bank_button;
    lv_obj_t *mt_return_button;
    lv_obj_t *mt_return_text;
    lv_obj_t *footing_text_4;
    lv_obj_t *top_bar_cont_5;
    lv_obj_t *banko_logo_4;
    lv_obj_t *time_label_tf_4;
    lv_obj_t *mt_aaccount_cont;
    lv_obj_t *money_transfer_text_2;
    lv_obj_t *account_number_text;
    lv_obj_t *mt_amount_tf_1;
    lv_obj_t *mt_return_button_2;
    lv_obj_t *mt_return_text_2;
    lv_obj_t *footing_text_6;
    lv_obj_t *top_bar_cont_6_1;
    lv_obj_t *banko_logo_6;
    lv_obj_t *time_label_tf_6;
    lv_obj_t *mt_amount_cont;
    lv_obj_t *money_transfer_text_1;
    lv_obj_t *amount_to_transfer_text;
    lv_obj_t *php_text;
    lv_obj_t *mt_amount_tf;
    lv_obj_t *mt_return_button_1;
    lv_obj_t *mt_return_text_1;
    lv_obj_t *footing_text_5;
    lv_obj_t *top_bar_cont_6;
    lv_obj_t *banko_logo_5;
    lv_obj_t *time_label_tf_5;
    lv_obj_t *dash_board_buttons_7;
    lv_obj_t *mt_pin_cont;
    lv_obj_t *money_transfer_text_3;
    lv_obj_t *enter_pin_text;
    lv_obj_t *mt_pin_tf_1;
    lv_obj_t *mt_pin_tf_2;
    lv_obj_t *mt_pin_tf_3;
    lv_obj_t *mt_pin_tf_4;
    lv_obj_t *footing_text_7;
    lv_obj_t *mt_return_button_3;
    lv_obj_t *mt_return_text_3;
    lv_obj_t *top_bar_cont_8;
    lv_obj_t *banko_logo_7;
    lv_obj_t *time_label_tf_7;
    lv_obj_t *bt_complete_cont;
    lv_obj_t *bt_comp_text;
    lv_obj_t *bt_return_button;
    lv_obj_t *bt_return_text;
    lv_obj_t *print_button;
    lv_obj_t *print_text;
    lv_obj_t *footing_text_8;
    lv_obj_t *bank_transfer_table;
    lv_obj_t *top_bar_cont_9;
    lv_obj_t *banko_logo_8;
    lv_obj_t *time_label_tf_8;
    lv_obj_t *cd_cont;
    lv_obj_t *cash_deposit_text_1;
    lv_obj_t *amount_to_transfer_text_1;
    lv_obj_t *php_text_1;
    lv_obj_t *cd_amount_tf;
    lv_obj_t *cd_return_button;
    lv_obj_t *cd_return_text;
    lv_obj_t *footing_text_9;
    lv_obj_t *top_bar_cont_6_2;
    lv_obj_t *banko_logo_9;
    lv_obj_t *time_label_tf_9;
    lv_obj_t *cd_success_cont;
    lv_obj_t *cash_deposit_success_text;
    lv_obj_t *cd_return_button_1;
    lv_obj_t *cd_return_return_button_1;
    lv_obj_t *print_button_1;
    lv_obj_t *print_text_1;
    lv_obj_t *footing_text_10;
    lv_obj_t *cd_table;
    lv_obj_t *top_bar_cont_9_1;
    lv_obj_t *banko_logo_10;
    lv_obj_t *time_label_tf_10;
    lv_obj_t *transac_history_cont;
    lv_obj_t *transaction_text;
    lv_obj_t *footing_text_11;
    lv_obj_t *transac_history_return_button;
    lv_obj_t *transac_history_return_text;
    lv_obj_t *transaction_table;
    lv_obj_t *top_bar_cont_12;
    lv_obj_t *banko_logo_11;
    lv_obj_t *time_label_tf_11;
    lv_obj_t *register_tfs;
    lv_obj_t *footing_text_12;
    lv_obj_t *obj0;
    lv_obj_t *personal_information;
    lv_obj_t *personal_information_1;
    lv_obj_t *last_name_1;
    lv_obj_t *firs_3;
    lv_obj_t *firs_4;
    lv_obj_t *personal_information_2;
    lv_obj_t *obj1;
    lv_obj_t *personal_information_3;
    lv_obj_t *last_name_2;
    lv_obj_t *personal_information_5;
    lv_obj_t *last_name_4;
    lv_obj_t *personal_information_6;
    lv_obj_t *last_name_5;
    lv_obj_t *top_bar_cont_13;
    lv_obj_t *banko_logo_12;
    lv_obj_t *time_label_tf_12;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_FINGERPRINT_SCAN = 2,
    SCREEN_ID_PIN = 3,
    SCREEN_ID_DASHBOARD = 4,
    SCREEN_ID_MONEY_TRANSFER = 5,
    SCREEN_ID_MT_ACCOUNT_NUM = 6,
    SCREEN_ID_MT_AMOUNT = 7,
    SCREEN_ID_MT_PIN_CONFIRMATION = 8,
    SCREEN_ID_BANK_TRANSFER_COMPLETE = 9,
    SCREEN_ID_CASH_DEPOSIT = 10,
    SCREEN_ID_CASH_DEPOSIT_COMPLETE = 11,
    SCREEN_ID_TRANSACTION_HISTORY = 12,
    SCREEN_ID_PERSONAL_INFO_REGISTRATION = 13,
};

void create_screen_main();
void tick_screen_main();

void create_screen_fingerprint_scan();
void tick_screen_fingerprint_scan();

void create_screen_pin();
void tick_screen_pin();

void create_screen_dashboard();
void tick_screen_dashboard();

void create_screen_money_transfer();
void tick_screen_money_transfer();

void create_screen_mt_account_num();
void tick_screen_mt_account_num();

void create_screen_mt_amount();
void tick_screen_mt_amount();

void create_screen_mt_pin_confirmation();
void tick_screen_mt_pin_confirmation();

void create_screen_bank_transfer_complete();
void tick_screen_bank_transfer_complete();

void create_screen_cash_deposit();
void tick_screen_cash_deposit();

void create_screen_cash_deposit_complete();
void tick_screen_cash_deposit_complete();

void create_screen_transaction_history();
void tick_screen_transaction_history();

void create_screen_personal_info_registration();
void tick_screen_personal_info_registration();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/
