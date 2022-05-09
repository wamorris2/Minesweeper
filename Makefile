CC = g++
CCFLAGS = -g -Wall -std=c++17

all: clean minesweeper

minesweeper: minesweeper.cpp 
	$(CC) $(CCFLAGS) $^ -o $@

clean:
	rm -f minesweeper.exe minesweeper *.swp