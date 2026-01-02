# Compiler & flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I.

# Source files
SRCS = main.c server.c file.c http.c queue.c
# Object files go in build/
OBJS = $(patsubst %.c,build/%.o,$(SRCS))

# Executable
TARGET = build/server

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files in build/
build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build folder exists
build:
	mkdir -p build

# Clean build folder
clean:
	rm -rf build/*

# Run the server with a PORT argument
# Usage: make run PORT=8080
run: all
	$(TARGET) $(PORT)
