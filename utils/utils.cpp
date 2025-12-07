#include "utils.hpp"
#include <fstream>

// ----- STATUS -----

const char* status[] = {
    "SUCCESS",
    "MISSING_FILE",
    "EMPTY_FILE"
};

// ----- TIMER -----

void Timer::start() {
    startTime = Clock::now();
}

void Timer::stop() {
    endTime = Clock::now();
    createTimestamp();
}

void Timer::createTimestamp() {

    auto duration = endTime - startTime;
    int64_t count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    
    int sec = count / 1000000000;
    int ms = (count % 1000000000) / 1000000;
    int us = (count % 1000000) / 1000;
    int ns = count % 1000;

    std::ostringstream oss;

    if (sec > 0) oss << sec << "s ";
    if (ms > 0) oss << ms << "ms ";
    if (us > 0) oss << us << "us ";
    if (ns > 0) oss << ns << "ns ";
   
    timestamp = oss.str();
}

// ----- FILE IO -----

Input::Input(const std::string name) {
    filename = name;
    std::ios_base::sync_with_stdio(false); // Optimize to not be compatible with C IO
}

STATUS Input::parseInput() {    
    STATUS result;

    timer.start();
   
    result = getRows();
    if (result != SUCCESS) {
        timer.stop();
        return result;
    }
    
    if (rows == 1) {
        result = parseRow();
    } else if (rows > 1) {
        result = parseRows();
    } else {
        result = EMPTY_FILE;
    }

    timer.stop();

    return result;
}

STATUS Input::getRows() {
    rows = 0;

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return MISSING_FILE;
    }

    char c;
    bool hasData = false;

    while (file.get(c)) {
        if (c == '\n') {
            rows++;
            hasData = false;
        } else if (c != '\r') {
            hasData = true;
        }
    }

    if (hasData) rows++;

    return SUCCESS;
}

STATUS Input::parseRow(char delim) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return MISSING_FILE;
    }

    std::string line;
    if (!std::getline(file, line)) {
        return SUCCESS;
    }

    data.reserve(line.length() / 8);

    std::istringstream iss(line);
    std::string token;

    while(std::getline(iss, token, delim)) {
        data.push_back(std::move(token));
    }

    return SUCCESS;
}

STATUS Input::parseRows() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return MISSING_FILE;
    }

    data.reserve(rows);

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(std::move(line));
    }

    return SUCCESS;
}

const std::string Input::getTime() const{
    return timer.timestamp;
}

// ----- Solution -----

std::string centerString(const std::string &str, int width) {
    int len = str.length();

    if (len >= width) return str;

    int padding  = width - len;
    int left = padding/2;
    int right  = padding - left;

    return std::string(left, ' ') + str + std::string(right, ' ');
}

Solution::Solution(int day, const std::string filename) : day(day), input(filename) {
    STATUS result = input.parseInput();
    if (result != SUCCESS)
        ERROR("Failed to parse input file", result);
}

void Solution::startTime(int part) {
    if (part == 1) {
        timer1.start();
    } else if (part == 2) {
        timer2.start();
    }
}

void Solution::stopTime(int part) {
    if (part == 1) {
        timer1.stop();
    } else if (part == 2) {
        timer2.stop();
    }
}
