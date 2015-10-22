CC=clang

readyQueueTest: readyQueueTest.c readyQueue.c
	$(CC) readyQueueTest.c readyQueue.c -o readyQueueTest
