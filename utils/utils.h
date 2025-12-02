#include <stdio.h>
#include <stdint.h>
#include <time.h>

// ----- TIMER -----

typedef struct timespec TIME; 
extern TIME EXECUTION_TIME;

void startTime();
void stopTime();

const char* getTimestamp(TIME t);

// ----- STATUS -----

typedef enum {
    SUCCESS,
    MISSING_FILE
} STATUS;

extern const char* status[];

#define ERROR(msg, code) printf("%s, CODE = %s\r\n", (msg), status[(code)])
#define SOLUTION(day, solution) printf("Day %u\r\nSolution: %u\r\nExecution Time: %s\r\n", (day), (solution), getTimestamp(EXECUTION_TIME));
// ----- FILE IO -----

#define FILENAME "input.txt"
extern uint32_t LINECOUNT;

STATUS getFileLineCount(const char* filename);

