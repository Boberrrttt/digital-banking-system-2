
#ifndef TRANSACTION_H
#define TRANSACTION_H

int createTransaction(const char* accountNumber, const char* type, double amount);
int getTransactionHistory(const char* accountNumber);

#endif
