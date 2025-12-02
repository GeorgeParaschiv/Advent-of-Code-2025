CC = gcc
CFLAGS = -Wall -g -I../utils
TARGET = solution
UTILS = ../utils
OBJECTS = solution.o $(UTILS)/utils.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	
solution.o: solution.c
	$(CC) $(CFLAGS) -c solution.c

$(UTILS)/utils.o: $(UTILS)/utils.c $(UTILS)/utils.h
	$(CC) $(CFLAGS) -c $(UTILS)/utils.c -o $(UTILS)/utils.o

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
