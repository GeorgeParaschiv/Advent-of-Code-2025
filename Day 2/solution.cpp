#include "utils.hpp"

#define DAY 2 
#define TYPE1 int
#define TYPE2 int

TYPE1 part1(Input input) {
    TYPE1 solution;

    return solution;
}

TYPE2 part2(Input input) {
    TYPE2 solution;

    return solution;
}

int main() {
    
    Solution solution(DAY);
    Results<TYPE1, TYPE2> results;
    
    solution.startTime(1);
    results.part1 = part1(solution.input);
    solution.stopTime(1);


    solution.startTime(2);
    results.part2 = part2(solution.input);
    solution.stopTime(2);

    solution.printResults(results);

    return 0;
}


