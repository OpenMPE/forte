# Author Leviathenn

# compile all source filoes in the src directoru

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)	# Replace .c with .y

CC = gcc	# Compiler

# compile all o files to a tmp directory than compile them to a library
all: $(OBJ)
	$(CC) -o ./build/libmodparser $(OBJ) 
	$(CC) -shared -o ./build/libmodparser.so $(OBJ) -rdynamic
# Compile all c files to a tmp directory
%.o: %.c
	$(CC) -c $< -o $@

# Clean all o files
clean:
	rm -f ./tmp/*.o