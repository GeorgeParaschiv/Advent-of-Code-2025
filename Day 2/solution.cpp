#include "utils.hpp"

#define DAY 2 
#define TYPE1 long
#define TYPE2 int

struct range {
    std::string start;
    std::string end;
};

range filterRange(std::string start, std::string end) {
    range r;

    int startLen = start.length();

    if (startLen % 2 == 0) {
        r.start = start.substr(0, startLen/2);

        if (stol(r.start + r.start) < stol(start)) {
            r.start = std::to_string(stol(r.start) + 1); 
        }
    } else {
        r.start = "1" + std::string(startLen/2, '0');
    }
    
    int endLen = end.length(); 

    if (endLen % 2 == 0) {
        r.end = end.substr(0, endLen/2);

        if (stol(r.end + r.end) > stol(end)) {
            r.end = std::to_string(stol(r.end) - 1); 
        }
    } else {
        r.end = std::string(endLen/2, '9'); 
    }

    return r;
}

TYPE1 part1(Input input) {
    TYPE1 solution = 0;
    
    for (const std::string &str : input.data) {
        int pos = str.find("-");
        //std::cout << "Range: " << str.substr(0, pos) << " - " << str.substr(pos+1) << std::endl;  
        range r = filterRange(str.substr(0, pos), str.substr(pos+1));
        
        //std::cout << "Filtered: " << r.start << " - " << r.end << std::endl << std::endl;  
        for (int s = stol(r.start); s <= stol(r.end); s++) {
            solution += stol(std::to_string(s) + std::to_string(s));
        }

    }

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


