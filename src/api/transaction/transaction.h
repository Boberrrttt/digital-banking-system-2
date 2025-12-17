
#ifndef TRANSACTION_H
#define TRANSACTION_H

int createTransaction(const char* accountNumber, const char* type, double amount);
int getTransactionHistory(const char* accountNumber);
int deduct_balance(const char* accountNumber, double amount);

#endif
