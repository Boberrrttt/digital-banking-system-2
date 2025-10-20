#include "moneyTransfer.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <time.h>

extern sqlite3 *db;

int inputReceiverAccount(const char* accountNumber){
  char sql[256];
  sqlite3_stmt *stmt;
  int rc, exists = 0;

  snprintf(sql, sizeof(sql),
         "SELECT COUNT(*) FROM users WHERE accountNumber = '%s';",
         receiverAccountNumber);

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
      fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
      return 0;
  }

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
      int count = sqlite3_column_int(stmt, 0);
      if (count == 1) exists = 1;
  }

  sqlite3_finalize(stmt);
  return exists;
}

// int inputMoney(double amount, const char* receiverAccount, const char* senderAccount) {
//   const sql[512];
//   sqlite3_stmt *stmt;
//   int rc;
//
//   snprintf(sql, sizeof(sql),
//            "SELECT balance FROM users WHERE accountNumber='%s';",
//            senderAccount);
//
//   rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
//   if (rc != SQLITE_OK) {
//       fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
//       return 0;
//   }
//
// }
