#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    char accountNumber[32];
    char name[64];
    double balance;
    char fingerprintId[32];
} UserProfile;

double getBalance(const char* accountId);
UserProfile getProfileDetails(const char* accountNumber);
void logout();
void createUser(const char* name, const char* fingerprintId, double balance);
int verifyPin();
UserProfile loginWithFingerprint(const char *fingerprintId);

#endif
