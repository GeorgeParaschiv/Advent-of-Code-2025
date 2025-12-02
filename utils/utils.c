#include "utils.h"

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

TIMER* PART1;
TIMER* PART2;

void initTimers() {
    PART1 = malloc(sizeof(TIMER));
    PART2 = malloc(sizeof(TIMER));
}

void freeTimers() {
    free(PART1);
    free(PART2);
}

void startTime(TIMER* tm) {
    clock_gettime(CLOCK_REALTIME, &tm->start);
}

void stopTime(TIMER* tm) {
    clock_gettime(CLOCK_REALTIME, &tm->end);
}

const char* getTimestamp(TIMER* tm) {
    static char timestamp[64];
    
    long long s = (long long) (tm->end.tv_sec - tm->start.tv_sec);
    long long ns = (long long) (tm->end.tv_nsec - tm->start.tv_nsec);

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


