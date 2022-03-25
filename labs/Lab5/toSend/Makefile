all: 
	gcc -pthread createThread.c -o createThread.o
	gcc -pthread joinThread.c -o joinThread.o
	gcc -pthread mutexThread.c -o mutexThread.o
	gcc -pthread conditionThread.c -o conditionThread.o

brige:
	gcc -pthread bridge.c -o bridge.o && ./bridge.o

clean: 
	rm -f *.o