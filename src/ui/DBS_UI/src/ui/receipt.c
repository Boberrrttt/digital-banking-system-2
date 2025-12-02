#include "receipt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VENDOR_ID  0x0fe6
#define PRODUCT_ID 0x811e

// ESC/POS commands
const unsigned char CMD_INIT[]         = {0x1B, 0x40};
const unsigned char CMD_ALIGN_CENTER[] = {0x1B, 0x61, 0x01};
const unsigned char CMD_ALIGN_LEFT[]   = {0x1B, 0x61, 0x00};
const unsigned char CMD_FEED[]         = {0x1B, 0x64, 0x03};
const unsigned char CMD_CUT[]          = {0x1D, 0x56, 0x00};

#define LINE_WIDTH 32

// Utility: justify left/right on same line
static void justify_line(char *buf, const char *left, const char *right) {
    int left_len = strlen(left);
    int right_len = strlen(right);
    int spaces = LINE_WIDTH - (left_len + right_len);
    if (spaces < 1) spaces = 1;
    snprintf(buf, LINE_WIDTH + 1, "%s%*s%s", left, spaces, "", right);
}

void print_receipt(const char* account_no, const char* amount, const char* transaction_type) {
    libusb_device_handle *handle = NULL;
    int r, transferred;

    // --- Time and date ---
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char date_str[16], time_str[16];
    snprintf(date_str, sizeof(date_str), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);

    // --- Initialize libusb ---
    r = libusb_init(NULL);
    if (r < 0) { fprintf(stderr, "libusb init error: %s\n", libusb_error_name(r)); return; }

    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (!handle) { fprintf(stderr, "⚠️ Printer not found.\n"); libusb_exit(NULL); return; }

    if (libusb_kernel_driver_active(handle, 0) == 1) libusb_detach_kernel_driver(handle, 0);
    r = libusb_claim_interface(handle, 0);
    if (r < 0) { fprintf(stderr, "⚠️ Cannot claim interface: %s\n", libusb_error_name(r)); libusb_close(handle); libusb_exit(NULL); return; }

    // --- Begin printing ---
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_INIT, sizeof(CMD_INIT), &transferred, 0);
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_ALIGN_CENTER, sizeof(CMD_ALIGN_CENTER), &transferred, 0);

    const char *header =
        "   GROUP ONE INC.\n"
        "       BANKKO\n"
        "1234 Fake Street, Nowhere City\n"
        "    Tel: (000) 123-4567\n"
        "--------------------------------\n";
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)header, strlen(header), &transferred, 0);

    // --- Transaction Info ---
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_ALIGN_LEFT, sizeof(CMD_ALIGN_LEFT), &transferred, 0);

    char line[LINE_WIDTH + 2];

    justify_line(line, "Transaction Type:", transaction_type);
    strcat(line, "\n");
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    justify_line(line, "Account No.:", account_no);
    strcat(line, "\n");
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    char amount_line[32];
    snprintf(amount_line, sizeof(amount_line), "Php %s", amount);
    justify_line(line, "Amount:", amount_line);
    strcat(line, "\n");
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    strncpy(line, "--------------------------------\n", LINE_WIDTH);
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    justify_line(line, "Date:", date_str);
    strcat(line, "\n");
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    justify_line(line, "Time:", time_str);
    strcat(line, "\n");
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    strncpy(line, "--------------------------------\n", LINE_WIDTH);
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)line, strlen(line), &transferred, 0);

    // --- Footer ---
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_ALIGN_CENTER, sizeof(CMD_ALIGN_CENTER), &transferred, 0);
    const char *footer = "Thank you for banking with us!\n\n\n";
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)footer, strlen(footer), &transferred, 0);

    // --- Feed and cut ---
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_FEED, sizeof(CMD_FEED), &transferred, 0);
    libusb_bulk_transfer(handle, 0x01, (unsigned char*)CMD_CUT, sizeof(CMD_CUT), &transferred, 0);

    // --- Clean up ---
    libusb_release_interface(handle, 0);
    libusb_close(handle);
    libusb_exit(NULL);

    printf("✅ Receipt printed successfully.\n");
}

