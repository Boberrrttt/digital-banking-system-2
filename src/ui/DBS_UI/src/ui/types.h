#ifndef TYPES_H
#define TYPES_H

// User struct
typedef struct User {
    char accountNumber[32];
    char name[64];
    double balance;
    int fingerprintId;
    char pin[32];
} User;

// Transaction struct
typedef struct Transaction {
    int id;
    char type[32];
    double amount;
    char date[16];
} Transaction;

#endif

