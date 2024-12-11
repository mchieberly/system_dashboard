# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Executable name
TARGET = system_stats

# Object file
O = system_stats.o

# Source file
SRC = system_stats.c

# Build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up executable
clean:
	rm -f $(TARGET)
