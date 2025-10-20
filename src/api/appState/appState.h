#ifndef APP_STATE_H
#define APP_STATE_H

typedef struct {
    char accountId[30];
    char accountName[50];
    double balance;
    int isLoggedIn;
} AppState;

extern AppState appState;

#endif

