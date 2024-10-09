# Author Leviathenn

# compile all source filoes in the src directoru

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)	# Replace .c with .y

CC = gcc	# Compiler

# Compile all o files to a tmp directory
all: $(OBJ)
	make ../modparser
	cp ../modparser/build/libmodparser.so ./build/
	$(CC) -o ./build/compiler ./tmp/$(OBJ) -ldl

# Compile all c files to a tmp directory
%.o: %.c
	$(CC) -c $< -o ./tmp/$@

# Clean all o files
clean:
	rm -f ./tmp/*.o