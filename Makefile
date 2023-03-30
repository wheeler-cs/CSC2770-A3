CC=g++
CFLAGS=-g -Wall -pedantic -c

EXECUTABLE=LineEditor

# Compile commands
all: build/main.o build/fn.o
	$(CC) $^ -o build/$(EXECUTABLE)

main.o: build/main.o
build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $< -o $@

fn.o: build/fn.o
build/fn.o: src/fn.cpp src/fn.hpp
	$(CC) $(CFLAGS) $< -o $@


# Utility commands
.PHONY: clean
clean:
	rm ./build/*

.PHONY: run
run:
	./build/$(EXECUTABLE)