compiler = gcc
file = main.c
target = main.exe
source = ./src/ark_algorithm.c ./src/ark_memory.c ./src/ark_log.c

running : compiling
	./main.exe

compiling :
	$(compiler) $(file) -o $(target) $(source)