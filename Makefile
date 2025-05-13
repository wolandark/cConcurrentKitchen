# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pthread
LDFLAGS = -lpthread

# Executable names
ALL_EXEC = kitchen_app

# Source files
SRC_SERVER = kitchen_server.c
SRC_CLIENT = order_client.c
SRC_MAIN = main.c

# Object files
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_MAIN = $(SRC_MAIN:.c=.o)

# Default target (build combined program)
all: $(ALL_EXEC)

# Build combined program (supports both server and client via args)
$(ALL_EXEC): $(OBJ_MAIN) $(OBJ_SERVER) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(ALL_EXEC) *.o

# Phony targets (not actual files)
.PHONY: all clean
