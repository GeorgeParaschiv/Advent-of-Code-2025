#include "utils.hpp"

#define DAY 1 
#define TYPE1 int
#define TYPE2 int

std::vector<int> readRotations(const std::vector<std::string> data) {
    std::vector<int> rotations;
    rotations.reserve(data.size());

    for (const std::string &str : data) {
        int value = std::stoi(str.substr(1));
        rotations.push_back(str[0] == 'R' ? value : -value);
    }

    return rotations;
}

int getNewPosition(int current, int rotation) {
   return ((current + rotation) % 100 + 100) % 100;
}

TYPE1 part1(const Input& input) {
    TYPE1 solution = 0;
    
    std::vector<int> rotations = readRotations(input.data);
    
    int position = 50;
    for (int rotation : rotations) {
        position = getNewPosition(position, rotation);
        
        if (position == 0) {
            solution++;
        }
    }

    return solution;
}

TYPE2 part2(const Input& input) {
    TYPE2 solution = 0;
    
    std::vector<int> rotations = readRotations(input.data);

    int position = 50;
    for (int rotation : rotations) {
        
        if (position == 0) {
            solution += std::abs(rotation / 100);
        } else {
            int temp = position + rotation;

            if (temp <= 0) {
                solution += (1 - temp / 100);
            } else if (temp >= 100) {
                solution += temp / 100;
            }
        }
        position = getNewPosition(position, rotation);
    }

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

