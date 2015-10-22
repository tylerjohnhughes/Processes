CC=clang

processes: processes.c readyQueue.c
	$(CC) processes.c readyQueue.c -o processes
