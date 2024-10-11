# Author Leviathenn

# compile all source filoes in the src directoru

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)	# Replace .c with .y

CC = gcc	# Compiler

# Compile all o files to a tmp directory
all: $(OBJ)
	$(CC) -o ./build/compiler $(OBJ) -ldl -lyaml

# Compile all c files to a tmp directory
%.o: %.c
	$(CC) -c $< -o $@

# Clean all o files
clean:
	rm -f *.o