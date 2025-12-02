#include "utils.h"

#define DAY 1

STATUS readRotations(int *rotations) {
    STATUS result = SUCCESS;
    
    FILE * fp = fopen(FILENAME, "r");
    if (!fp) {
        result = MISSING_FILE;
    } else {
        char direction; 
        int value;
        for (uint32_t i = 0; i < LINECOUNT; i++) {
            fscanf(fp, " %c%d", &direction, &value);
            if (direction == 'L') value = -value;
            rotations[i] = value %= 100;
        }

        fclose(fp);
    }

    return result;
}

uint32_t numZeros(int* rotations) {
    
    int start = 50;
    uint32_t count = 0;
    for (uint32_t i = 0; i < LINECOUNT; i++) {
        if (rotations[i] > 0) {
            printf("%d + %d = ", start, rotations[i]); 
        } else {
            printf("%d %d = ", start, rotations[i]);
        }
        start += (rotations[i]);

        if (start < 0) {
            start += 100;
        } else if (start >= 100) {
            start -= 100;
        }

        printf("%d\r\n", start);

        if (start == 0) {
            count++;
        }
    }

    return count;
}

STATUS solve(uint32_t *solution) {
    STATUS result = SUCCESS;
    int rotations[LINECOUNT];
    
    startTime();

    if ((result = readRotations(rotations)) != SUCCESS) {
       ERROR("Failed to read rotations from input file", result);
    } else {
       *solution = numZeros(rotations); 
    }

    stopTime();

    return result;
}

int main() {
    
    STATUS result = SUCCESS;
    if ((result = getFileLineCount(FILENAME)) != SUCCESS) {
        ERROR("Failed to get line count from input file", result);
    }

    uint32_t solution = 0;
    if ((result = solve(&solution)) != SUCCESS) {
        ERROR("Error when trying to find the solution, CODE = %s\r\n", result);
    } else {
        SOLUTION(DAY, solution);
    }

    return 0;
}
