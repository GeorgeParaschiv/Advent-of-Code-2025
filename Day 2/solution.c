#include "utils.h"

#define DAY 2 

typedef struct solution {
    uint32_t part1;
    uint32_t part2;
} solution;

STATUS solve(solution* sols) {
    STATUS result = SUCCESS;
    
    // ----- PART 1 -----

    startTime(PART1);    



    stopTime(PART1);
    
    // ----- PART 2 -----

    startTime(PART2);



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

