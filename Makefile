CC = clang++
BIN = scan

.PHONY: main.cpp
all: main.cpp
	$(CC) $< -o $(BIN)
