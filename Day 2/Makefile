CXX = g++
CXXFLAGS = -Wall -O3 -ffast-math -I../utils -std=c++17
TARGET = solution
UTILS = ../utils
OBJECTS = solution.o $(UTILS)/utils.o

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	
solution.o: solution.cpp
	$(CXX) $(CXXFLAGS) -c solution.cpp

$(UTILS)/utils.o: $(UTILS)/utils.cpp $(UTILS)/utils.hpp
	$(CXX) $(CXXFLAGS) -c $(UTILS)/utils.cpp -o $(UTILS)/utils.o

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
