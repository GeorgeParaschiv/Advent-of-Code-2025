#include <vector>
#include <string>
#include <chrono>

#include <iostream>
#include <sstream>
#include <iomanip>
// ----- STATUS -----

typedef enum {
    SUCCESS,
    MISSING_FILE,
    EMPTY_FILE
} STATUS;

extern const char* status[];

#define ERROR(msg, code) std::cout << (msg) << ", CODE = " << status[(code)] << std::endl;

// ----- TIMER -----

using Clock = std::chrono::high_resolution_clock;
using Time = std::chrono::time_point<Clock>;

class Timer {
    Time startTime;
    Time endTime;
    
    void createTimestamp();
    
    public:
        Timer() = default;
        
        void start();
        void stop();

        std::string timestamp;
};

// ----- FILE IO -----

class Input {
    std::string filename;
    Timer timer;
    
    STATUS getRows();
    STATUS parseRows();
    STATUS parseRow(char delim = ',');

    public:
        Input(const std::string name = "input.txt");
       
        STATUS parseInput();
        const std::string getTime() const;
        
        int rows;
        std::vector<std::string> data;
};

// ----- SOLUTION -----

std::string centerString(const std::string &str, int width);

template<typename T1, typename T2>
struct Results {
    T1 part1;
    T2 part2;

    Results() : part1(), part2() {}
};

class Solution { 
    Timer timer1;
    Timer timer2; 
    int day;
    
    template<typename T>        
    std::string formatSolution(const T& solution) const;
    
    public:
        Solution(int day, const std::string filename = "input.txt");
        
        void startTime(int part);
        void stopTime(int part);

        template<typename T1, typename T2>
        void printResults(const Results<T1, T2>& results) const;

        Input input;
};

template<typename T>
std::string Solution::formatSolution(const T& solution) const {
    std::ostringstream oss;
    oss << solution;
    return oss.str();
}

template<typename T1, typename T2> 
void Solution::printResults(const Results<T1, T2>& results) const {
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Day " << std::setfill('0') << std::setw(2) << day 
              << " |                Solution                |             Execution Time             |" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Input  | " << centerString("Parsed " + std::to_string(input.data.size()) + " lines", 38)
              << " | " << centerString(input.getTime(), 38) << " |" << std::endl;
    std::cout << "Part 1 | " << centerString(formatSolution(results.part1), 38) 
              << " | " << centerString(timer1.timestamp, 38) << " |" << std::endl;
    std::cout << "Part 2 | " << centerString(formatSolution(results.part2), 38)
              << " | " << centerString(timer2.timestamp, 38) << " |" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------" << std::endl;
}
