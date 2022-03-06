#include <stdio.h>

#include "../headers/utils.h"
#include "../headers/common.h"

void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int read_int_option(const char* msg) {
    printf("%s", msg);
    int option;
    int matches = scanf("%d", &option);
    if (matches != 1) {
        option = INVALID_OPTION;
    }
    flush_input();
    return option;
}

char read_char_option(const char* msg) {
    printf("%s", msg);

    char buffer[2];
    char* result = fgets(buffer, 2, stdin);

    char option = '\0';
    if (result != NULL && buffer[0] != '\n') {
        option = buffer[0];
        flush_input();
    }
    return option;
}


void log_info(FILE* fd, char* msg) {
    if (LOG_LEVEL >= INFO_LEVEL) {
        fprintf(fd, "INFO: %s\n", msg);
        fflush(fd);
    }
}

void log_warn(FILE* fd, char* msg) {
    if (LOG_LEVEL >= WARN_LEVEL) {
        fprintf(fd,"WARNING: %s\n", msg);
        fflush(fd);
    }
}

void log_error(FILE* fd, char* msg) {
    if (LOG_LEVEL >= ERROR_LEVEL) {
        fprintf(fd,"ERROR: %s\n", msg);
        fflush(fd);
    }
}
