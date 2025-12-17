#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    int id;
    char accountNumber[20];
    char type[20];
    double amount;
    char date[30];
} Transaction;

int createTransaction(const char* accountNumber, const char* type, double amount) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db);
    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql =
        "INSERT INTO transactions (accountNumber, type, amount) VALUES (?, ?, ?);";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, type, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, amount);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Failed to insert transaction: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 1; 
}

int getTransactionHistory(const char* accountNumber, Transaction* transactions, int maxCount) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc, count = 0;

    rc = sqlite3_open("banking.db", &db);
    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql =
        "SELECT id, accountNumber, type, amount, date "
        "FROM transactions WHERE accountNumber = ? ORDER BY date DESC;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);

    while (sqlite3_step(stmt) == SQLITE_ROW && count < maxCount) {
        transactions[count].id = sqlite3_column_int(stmt, 0);
        strcpy(transactions[count].accountNumber, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(transactions[count].type, (const char*)sqlite3_column_text(stmt, 2));
        transactions[count].amount = sqlite3_column_double(stmt, 3);
        strcpy(transactions[count].date, (const char*)sqlite3_column_text(stmt, 4));
        count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count; 
}

int deduct_balance(const char* accountNumber, double amount) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double current_balance;

    rc = sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db);
    if (rc != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Get current balance
    const char *sql_select = "SELECT balance FROM users WHERE accountNumber = ?;";
    rc = sqlite3_prepare_v2(db, sql_select, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        current_balance = sqlite3_column_double(stmt, 0);
    } else {
        printf("Account not found.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    sqlite3_finalize(stmt);

    if (current_balance < amount) {
        printf("Insufficient balance.\n");
        sqlite3_close(db);
        return 0;
    }

    // Deduct the amount
    const char *sql_update = "UPDATE users SET balance = balance - ? WHERE accountNumber = ?;";
    rc = sqlite3_prepare_v2(db, sql_update, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare update statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_double(stmt, 1, amount);
    sqlite3_bind_text(stmt, 2, accountNumber, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Failed to update balance: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 1; // Success
}
