#include "account.h"
#include "/root/Desktop/test/lv_port_linux/src/ui/DBS_UI/src/ui/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>

extern sqlite3 *db;

UserProfile getUserByFingerprint(const char *fingerprintId) {
    UserProfile user = {"", "", 0.0, ""};
    sqlite3_stmt *stmt;

    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) != SQLITE_OK) {
        fprintf(stderr, "❌ Cannot open database: %s\n", sqlite3_errmsg(db));
        return user;
    }

    const char *sql = "SELECT accountNumber, name, balance FROM users WHERE fingerprintId = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return user;
    }

    sqlite3_bind_text(stmt, 1, fingerprintId, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(user.accountNumber, (const char *)sqlite3_column_text(stmt, 0));
        strcpy(user.name, (const char *)sqlite3_column_text(stmt, 1));
        user.balance = sqlite3_column_double(stmt, 2);
        strcpy(user.fingerprintId, fingerprintId);
    } else {
        printf("⚠️ No user found for fingerprint ID %s\n", fingerprintId);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user;
}

void createUser(const char* name, const char* fingerprintId, double balance) {
  char accountNumber[11];
  
  srand(time(NULL));

   for (int i = 0; i < 10; i++) {
      accountNumber[i] = '0' + rand() % 10;
  }
  accountNumber[10] = '\0';

  char sql[512];
  snprintf(sql, sizeof(sql),
      "INSERT INTO users(accountNumber, fingerprintId, name, balance) "
        "VALUES('%s', '%s', '%s', '%s');",
        accountNumber, fingerprintId, name, balance);
  
  char *err_msg = 0;
  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
  } else {
      printf("User created successfully!\nAccount Number: %s, Name: %s\n",
             accountNumber, name);
  }
}

int verifyPin() {
    char sql[256];
    sqlite3_stmt *stmt;
    int rc, result = 0;

    // Build SQL query safely
    snprintf(sql, sizeof(sql),
             "SELECT COUNT(*) FROM users WHERE accountNumber = '%s' AND pin = '%s';",
             accountNumber, pin);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        if (count == 1) {
            result = 1;  // PIN is correct for this account
        }
    }

    sqlite3_finalize(stmt);
    return result;
}


double getBalance (const char* accountId) {
  char sql[256];
  sqlite3_stmt *stmt;
  double balance = 0.0;

  sprintf(sql, "SELECT balance FROM users WHERE accountNumber='%s';", accountId);
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
      fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      return 0.0;
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
      balance = sqlite3_column_double(stmt, 0);
  } else {
      printf("Account not found.\n");
  }

  sqlite3_finalize(stmt);
  return balance;
}

UserProfile getProfileDetails(const char* accountNumber) {
    UserProfile user = {"", "", 0.0, ""};
    sqlite3_stmt *stmt;

    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) != SQLITE_OK) {
        fprintf(stderr, "❌ Cannot open database: %s\n", sqlite3_errmsg(db));
        return user;
    }

    const char *sql = "SELECT accountNumber, name, balance FROM users WHERE accountNumber = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return user;
    }

    sqlite3_bind_text(stmt, 1, accountNumber, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(user.accountNumber, (const char *)sqlite3_column_text(stmt, 0));
        strcpy(user.name, (const char *)sqlite3_column_text(stmt, 1));
        user.balance = sqlite3_column_double(stmt, 2);
        strcpy(user.fingerprintId, accountNumber);
    } else {
        printf("⚠️ No user found for fingerprint ID %s\n", accountNumber);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return user;
  
}

UserProfile loginWithFingerprint(const char *fingerprintId) {
    UserProfile user = {"", "", 0.0, ""};
    sqlite3_stmt *stmt;

    printf("🔍 Attempting fingerprint login for ID: %s\n", fingerprintId);

    // Open the SQLite database
    if (sqlite3_open("/root/Desktop/test/lv_port_linux/src/api/bank.db", &db) != SQLITE_OK) {
        fprintf(stderr, "❌ Cannot open database: %s\n", sqlite3_errmsg(db));
        return user;
    }

    // Prepare SQL query
    const char *sql = "SELECT accountNumber, name, balance FROM users WHERE fingerprintId = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "❌ Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return user;
    }

    // Bind fingerprint ID parameter
    sqlite3_bind_text(stmt, 1, fingerprintId, -1, SQLITE_STATIC);

    // Execute the query and fetch user data
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(user.accountNumber, (const char *)sqlite3_column_text(stmt, 0));
        strcpy(user.name, (const char *)sqlite3_column_text(stmt, 1));
        user.balance = sqlite3_column_double(stmt, 2);
        strcpy(user.fingerprintId, fingerprintId);

        printf("✅ Login successful!\n");
        printf("   Name: %s\n", user.name);
        printf("   Account: %s\n", user.accountNumber);
        printf("   Balance: %.2f\n", user.balance);
    } else {
        printf("⚠️ No user found for fingerprint ID %s\n", fingerprintId);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // If login failed, return a default guest profile
    if (strlen(user.accountNumber) == 0 || strlen(user.name) == 0) {
        UserProfile guest = {"0000000000", "Guest", 0.0, ""};
        return guest;
    }

    return user;
}

void logout() {
  printf("User logged out");
}
