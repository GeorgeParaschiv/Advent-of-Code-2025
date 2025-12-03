#include "utils.h"

#define DAY 1

typedef struct solution {
    uint32_t part1;
    uint32_t part2;
} solution;

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
            rotations[i] = value;
        }

        fclose(fp);
    }

    return result;
}

int getNewPosition(int current, int rotation) {
   current = (current + rotation) % 100;

   if (current < 0) current += 100;

   return current;
}

uint32_t numZeros(int* rotations) {
    int position = 50;
    uint32_t count = 0;
    
    for (uint32_t i = 0; i < LINECOUNT; i++) {
        position = getNewPosition(position, rotations[i]);
        
        if (position == 0) {
            count++;
        }
    }

    return count;
}

uint32_t zerosCrossed(int* rotations) {
    int position = 50;
    int crossings = 0;
    uint32_t count = 0;
    for (uint32_t i = 0; i < LINECOUNT; i++) {
        if (position == 0) {
            crossings = rotations[i]/100;
        } else {
            int temp = position + rotations[i];

            if (temp <= 0) {
                count += 1;
                crossings = temp / 100;
            } else if (temp >= 100) {
                crossings = temp / 100;
            } else {
                crossings = 0;
            }
        }

        if (crossings < 0) {
            count -= crossings;
        } else { 
            count += crossings;
        }
        
        position = getNewPosition(position, rotations[i]);
    }
    return count;
}

STATUS solve(solution *sols) {
    STATUS result = SUCCESS;
    int rotations[LINECOUNT];

    // ----- PART 1 -----

    startTime(PART1);    

    if ((result = readRotations(rotations)) != SUCCESS) {
       ERROR("Failed to read rotations from input file", result);
    } else {
       sols->part1 = numZeros(rotations); 
    }

    stopTime(PART1); 
    
    // ----- PART 2 -----

    startTime(PART2);

    sols->part2 = zerosCrossed(rotations);

    stopTime(PART2);

    return result;
}

int main() {
    
    initTimers();

    STATUS result = SUCCESS;
    if ((result = getFileLineCount(FILENAME)) != SUCCESS) {
        ERROR("Failed to get line count from input file", result);
    }

    solution sols = { 0 };
    if ((result = solve(&sols)) != SUCCESS) {
        ERROR("Error when trying to find the solution, CODE = %s\r\n", result);
    } else {
        printf("------------------------------------------------------------------------------------------\r\n");
        printf("Day %02d |                Solution                |             Execution Time             |\r\n", DAY);
        printf("------------------------------------------------------------------------------------------\r\n");
        printf("Part 1 | %-38u | %-38s |\r\n", sols.part1, getTimestamp(PART1));
        printf("Part 2 | %-38u | %-38s |\r\n", sols.part2, getTimestamp(PART2));
        printf("------------------------------------------------------------------------------------------\r\n");
    }

    freeTimers();

    return 0;
}
