#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <lvgl/lvgl.h>
#include <stdlib.h>
#include "../../../../api/transaction/transaction.h"
#include "ui.h"
#include "screens.h"
#include "globals.h"
#include "receipt.h"
#include "actions.h"
#include "types.h"

extern lv_obj_t *objects_balance_tf;
extern lv_obj_t *objects_transaction_history;
extern char userAccountNumber[];

FILE *fp_fingerprint = NULL;
lv_timer_t *fingerprint_timer = NULL;

volatile int billPulseCount = 0;
volatile int billDetected = 0;
double billValue = 0.0;


void refresh_transaction_history_table() {
    // Check that the user is logged in and the table exists
    if (!currentUser || !transaction_list) {
        printf("[ERROR] Cannot refresh table: user or table is NULL\n");
        return;
    }

    int count = 0;
    // Fetch transactions for the logged-in user
    Transaction* txs = fetch_transaction_history(userAccountNumber, &count);

    // Ensure at least the header row exists
    lv_table_set_row_cnt(transaction_list, (count > 0 ? count : 0) + 1);

    // Set column headers
    const char* headers[] = {"ID", "Type", "Amount", "Date"};
    for (int c = 0; c < 4; c++) {
        lv_table_set_cell_value(transaction_list, 0, c, headers[c]);
    }

    // Fill the table rows with transaction data
    if (txs != NULL && count > 0) {
        char buf[32];
        for (int r = 0; r < count; r++) {
            // ID
            snprintf(buf, sizeof(buf), "%d", txs[r].id);
            lv_table_set_cell_value(transaction_list, r + 1, 0, buf);

            // Type
            lv_table_set_cell_value(transaction_list, r + 1, 1, txs[r].type);

            // Amount
            snprintf(buf, sizeof(buf), "%.2f", txs[r].amount);
            lv_table_set_cell_value(transaction_list, r + 1, 2, buf);

            // Date
            lv_table_set_cell_value(transaction_list, r + 1, 3, txs[r].date);
        }

        free(txs);
    } else {
        printf("[INFO] No transactions found for user %s\n", currentUser->name);
    }
}

int run_fingerprint_auth() {
    char buffer[128];
    int finger_id = 0;

    fp_fingerprint = popen("/bin/bash -c 'source /root/fingerprint-env/bin/activate && python3 -u /root/find.py'", "r");
    if (fp_fingerprint == NULL) {
        printf("Failed to run fingerprint script\n");
        return 0;
    }

    if (fgets(buffer, sizeof(buffer), fp_fingerprint) != NULL) {
        finger_id = atoi(buffer);
    }

    currentFingerId = finger_id;

    return finger_id;
}

Transaction* fetch_transaction_history(const char* accountNumber, int *count) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    *count = 0;

    // Open database
    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    const char *sql =
        "SELECT id, type, amount, date "
        "FROM transactions "
        "WHERE accountNumber = ? "
        "ORDER BY date DESC;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);

    // First, count rows
    int row_count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) row_count++;

    // Reset statement to fetch again
    sqlite3_reset(stmt);

    Transaction* transactions = malloc(sizeof(Transaction) * row_count);
    if (!transactions) {
        printf("Memory allocation failed\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        transactions[i].id = sqlite3_column_int(stmt, 0);
        strncpy(transactions[i].type, (const char*)sqlite3_column_text(stmt, 1), sizeof(transactions[i].type)-1);
        transactions[i].type[sizeof(transactions[i].type)-1] = '\0';
        transactions[i].amount = sqlite3_column_double(stmt, 2);
        strncpy(transactions[i].date, (const char*)sqlite3_column_text(stmt, 3), sizeof(transactions[i].date)-1);
        transactions[i].date[sizeof(transactions[i].date)-1] = '\0';
        i++;
    }

    *count = row_count;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return transactions;
}

void refresh_balance_display(const char* accountNumber) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    double balance = 0.0;

    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) == SQLITE_OK) {
        const char *sql = "SELECT balance FROM users WHERE accountNumber = ?;";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                balance = sqlite3_column_double(stmt, 0);
            }
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }

    char balanceText[64];
    snprintf(balanceText, sizeof(balanceText), "Php %.2f", balance);

    if (objects.balance_tf) {
        lv_label_set_text(objects.balance_tf, balanceText);
    }
}

User* get_user_by_fingerprint(int fingerprintId) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    User *user = malloc(sizeof(User));
    if (!user) return NULL;

    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        free(user);
        return NULL;
    }

    const char *sql =
        "SELECT accountNumber, name, balance, fingerprintId, pin "
        "FROM users WHERE fingerprintId = ? LIMIT 1;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(user);
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, fingerprintId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strncpy(user->accountNumber, (const char*)sqlite3_column_text(stmt, 0), sizeof(user->accountNumber)-1);
        strncpy(user->name, (const char*)sqlite3_column_text(stmt, 1), sizeof(user->name)-1);
        user->balance = sqlite3_column_double(stmt, 2);
        user->fingerprintId = sqlite3_column_int(stmt, 3);
        strncpy(user->pin, (const char*)sqlite3_column_text(stmt, 4), sizeof(user->pin)-1);

        // Assign to global so other screens can access
        currentUser = user;

        // Print for debug
        printf("User details:\n");
        printf("Account Number: %s\n", user->accountNumber);
        printf("Name: %s\n", user->name);
        printf("Balance: %.2f\n", user->balance);
        printf("Fingerprint ID: %d\n", user->fingerprintId);
        printf("PIN: %s\n", user->pin);

    } else {
        printf("No user found for fingerprint: %d\n", fingerprintId);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(user);
        return NULL;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user; 
}

void fingerprint_timer_cb(lv_timer_t *timer) {
    LV_UNUSED(timer);

    int finger_id = run_fingerprint_auth();

    if (finger_id > 0) {
        printf("Fingerprint matched: %d\n", finger_id);

        // Stop timer
        if (fingerprint_timer) {
            lv_timer_del(fingerprint_timer);
            fingerprint_timer = NULL;
        }

        // Close the Python process
        if (fp_fingerprint) {
            pclose(fp_fingerprint);
            fp_fingerprint = NULL;
        }

        // Free previous user data if any
        if (currentUser) {
            free(currentUser);
            currentUser = NULL;
        }

        // Fetch the user data from DB and store in global
        currentUser = get_user_by_fingerprint(finger_id);
        if (currentUser) {
            // Update global account number
            strncpy(userAccountNumber, currentUser->accountNumber, sizeof(userAccountNumber) - 1);
            userAccountNumber[sizeof(userAccountNumber) - 1] = '\0';

            printf("Logged in user: %s | Balance: %.2f\n", currentUser->name, currentUser->balance);

	    if (currentUser) {
	    printf("Logged in user: %s | Balance: %.2f\n", currentUser->name, currentUser->balance);

	    // 1. Create all user screens (do not load any yet)
	    create_screen_dashboard();
	    create_screen_transaction_history();

	    // 2. Load the dashboard screen explicitly
	    lv_scr_load(objects.dashboard);

	    // 3. Refresh transaction table (screen is not loaded, but table object exists)
	    refresh_transaction_history_table();
	}

        } else {
            printf("No user found for fingerprint %d\n", finger_id);
        }

    } else {
        printf("Fingerprint not found\n");
    }
}


void action_switch_to_fingerprint(lv_event_t * e) {
    printf("Switch to fingerprint screen\n");
    lv_scr_load(objects.fingerprint_scan);
    fingerprint_timer = lv_timer_create(fingerprint_timer_cb, 100, NULL);
}

void action_switch_to_pin(lv_event_t * e) {
    printf("Switch to pin screen\n");
    lv_scr_load(objects.pin);
}

void action_switch_to_main(lv_event_t * e) {
    printf("Switch to main screen (logout)\n");

    // Load main screen
    lv_scr_load(objects.main);

    // Delete other screens if they exist
    if (objects.dashboard) {
        lv_obj_del(objects.dashboard);
        objects.dashboard = NULL;
    }

    if (objects.transaction_history) {
        lv_obj_del(objects.transaction_history);
        objects.transaction_history = NULL;
    }

    if (objects.fingerprint_scan) {
        lv_obj_del(objects.fingerprint_scan);
        objects.fingerprint_scan = NULL;
    }

    if (objects.money_transfer) {
        lv_obj_del(objects.money_transfer);
        objects.money_transfer = NULL;
    }

    // ...repeat for any other dynamic screens created at runtime

    // Optional: reset any global user data
    if (currentUser) {
        free(currentUser);
        currentUser = NULL;
    }
    userAccountNumber[0] = '\0';

    create_screens();
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
    if (!objects.transaction_history) {
        printf("[ERROR] Transaction history screen not created yet!\n");
        return;
    }

    printf("Switch to transaction history screen\n");
    // Load the screen
    lv_scr_load(objects.transaction_history);
        // Refresh table content
    refresh_transaction_history_table();

}

void action_switch_to_account_num(lv_event_t * e) {
    printf("Switch to account number screen\n");
}

void action_switch_to_amount(lv_event_t * e) {
    printf("Switch to amount screen\n");
}

void action_switch_to_bank_transfer_complete(lv_event_t * e) {
    printf("Switch to bank transfer complete\n");

    double amt = atof(amount);
    const char* user_account = accountNumber;

    if (deduct_balance(user_account, amt)) {
        createTransaction(user_account, "Money Transfer", amt);
        refresh_balance_display(user_account); // 🔥 update dashboard in real time
        printf("✅ Amount %.2f deducted and transaction recorded.\n", amt);
    } else {
        printf("❌ Transaction failed (insufficient balance or error).\n");
    }

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



