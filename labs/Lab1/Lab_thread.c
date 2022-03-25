#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <string.h>

struct arg_struct {
    int pid;
    int numberOfPrimes;
};

int isDivisorOf(int x, int y){
    return (x % y) == 0;
} 

void calcPrimes(int numberOfPrimes, int pid) {
    int number = 2;
    int printedPrimes = 1;
    while(printedPrimes <= numberOfPrimes){
        //sleep(0.5);
        int isPrimeFlag = 1;
        int i;
        for(i = 2; i<number; i++ ){
            if(isDivisorOf(number, i)){
                isPrimeFlag = 0;
                break;
            }
        }
        if(isPrimeFlag){
            printf("Thread: %d : El número %d es Primo. \n", pid, number);
            printedPrimes++;
        }
        number++;
    }
}

void *myThread(void *vargp) {
    struct arg_struct *args = (struct arg_struct *)vargp; 
	calcPrimes( args->numberOfPrimes , args->pid);
}

int main ( int argc , char * argv []) {
    printf("### Primos threads ###\n"); 
	char* tmp = (char*)malloc(10 * sizeof(char));
	printf("Numero de primos: ");
	scanf("%s", tmp);
    int int_tmp = atoi(tmp);
    free(tmp);

    if(int_tmp <= 1 ){
        printf("Numero no valido.\n"); 
        return 0;
    }
    

    pthread_t tid1, tid2; 
    struct arg_struct args1;
    args1.pid = tid1;
    args1.numberOfPrimes = int_tmp;

    struct arg_struct args2;
    args2.pid = tid2;
    args2.numberOfPrimes = int_tmp;

	pthread_create(&tid1, NULL, myThread, (void *)&args1 );
	pthread_create(&tid2, NULL, myThread, (void *)&args2 );

	pthread_join(tid1, NULL);  
    pthread_join(tid2, NULL);  
        
	return 0;
}