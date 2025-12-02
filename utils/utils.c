#include "utils.h"
#include <bits/time.h>
#include <sys/time.h>
#include <time.h>

// ----- STATUS -----

const char* status[] = {
    "SUCCESS",
    "MISSING_FILE"
};

// ----- FILE IO -----

uint32_t LINECOUNT = 0;

STATUS getFileLineCount(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: file pointer is null.\r\n");
        return MISSING_FILE;
    }
    
    int ch;
    while((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') LINECOUNT++;
    }
    
    fclose(fp);
    return SUCCESS;
}       

// ----- TIMER -----


TIME START, END, EXECUTION_TIME = { 0 };

const char* getTimestamp(TIME t) {
    static char timestamp[64];

    long long s = (long long) t.tv_sec;
    long long ns = (long long) t.tv_nsec;

    if (ns < 0) ns = 0;

    long long ms = ns / 1000000;
    ns %= 1000000;

    long long us = ns / 1000;
    ns %= 1000;

    if (s > 0) {
        snprintf(timestamp, sizeof(timestamp), "%lld s %lld ms %lld us %lld ns", s, ms, us, ns);
    } else if (ms > 0) {
        snprintf(timestamp, sizeof(timestamp), "%lld ms %lld us %lld ns", ms, us, ns);
    } else if (us > 0) {
        snprintf(timestamp, sizeof(timestamp), "%lld us %lld ns", us, ns);
    } else {
        snprintf(timestamp, sizeof(timestamp), "%lld ns", ns);
    }

    return timestamp;
}

void startTime() {
    clock_gettime(CLOCK_REALTIME, &START);
}

void stopTime() {
    clock_gettime(CLOCK_REALTIME, &END);

    EXECUTION_TIME.tv_sec = END.tv_sec - START.tv_sec;
    EXECUTION_TIME.tv_nsec = END.tv_nsec - START.tv_nsec;
}

