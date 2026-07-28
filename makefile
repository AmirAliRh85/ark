compiler = gcc
file = main.c
target = main.exe
source = ./src/ark_Vector.c
source += ./src/ark_memory.c ./src/ark_log.c ./src/ark_Queue.c ./src/ark_Gapbuffer.c ./src/ark_Stack.c ./src/ark_Array.c ./src/ark_Hashmap.c

running : compiling
	./main.exe

compiling :
	$(compiler) $(file) -o $(target) $(source)