source = ../src/ark_algorithm.c ../src/ark_memory.c ../src/ark_log.c ../src/ark_Queue.c ../src/ark_Gapbuffer.c

# ark_log_test.c -> passed all test (multi threading can be implemented)

run : 
	gcc ./ark_log_test.c -o ark_log_test.exe $(source)
	gcc ./ark_memory_test.c -o ark_memory_test.exe $(source)
	gcc ./ark_algorithm_test.c -o ark_algorithm_test.exe $(source)