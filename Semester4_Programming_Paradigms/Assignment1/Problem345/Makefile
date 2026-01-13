# Compiler and Flags
CC = g++
CFLAGS = -Wall -g
LIB_NAME = lib_recursion.a

all: client_program

client_program: main.o $(LIB_NAME)
	$(CC) $(CFLAGS) main.o -L. -l_recursion -o client_program

$(LIB_NAME): array_utils.o string_utils.o
	ar rcs $(LIB_NAME) array_utils.o string_utils.o

array_utils.o: array_utils.cpp array_utils.h
	$(CC) $(CFLAGS) -c array_utils.cpp

string_utils.o: string_utils.cpp string_utils.h
	$(CC) $(CFLAGS) -c string_utils.cpp

main.o: main.cpp array_utils.h string_utils.h
	$(CC) $(CFLAGS) -c main.cpp

# Clean target
clean:
	del /f /q *.o *.a client_program.exe	
#rm -f *.o *.a client_program
