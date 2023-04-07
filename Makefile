CC=g++
CFLAGS=-g -Wall -pedantic -c

EXECUTABLE=edlin

# Compile commands
all: build/main.o build/edlin.o
	$(CC) $^ -o build/$(EXECUTABLE)

main.o: build/main.o
build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $< -o $@

edlin.o: build/edlin.o
build/edlin.o: src/edlin.cpp src/edlin.hpp
	$(CC) $(CFLAGS) $< -o $@


# Utility commands
.PHONY: clean
clean:
	rm ./build/*

.PHONY: run
run:
	./build/$(EXECUTABLE)