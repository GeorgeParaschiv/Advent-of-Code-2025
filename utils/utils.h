#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// ----- TIMER -----

typedef struct timespec TIME;

typedef struct timer {
    TIME start;
    TIME end;
} TIMER;

extern TIMER* PART1;
extern TIMER* PART2;

void initTimers();
void freeTimers();

void startTime(TIMER* tm);
void stopTime(TIMER* tm);

const char* getTimestamp(TIMER* tm);

// ----- STATUS -----

typedef enum {
    SUCCESS,
    MISSING_FILE
} STATUS;

extern const char* status[];

#define ERROR(msg, code) printf("%s, CODE = %s\r\n", (msg), status[(code)])

// ----- FILE IO -----

#define FILENAME "input.txt"
extern uint32_t LINECOUNT;

STATUS getFileLineCount(const char* filename);

