#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <string.h>

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
            printf("Process %d: El número %d es Primo. \n", pid, number);
            printedPrimes++;
        }
        number++;
    } 
} 



int main ( int argc , char * argv []) {
    printf("### Primos process ###\n"); 
	char* tmp = (char*)malloc(10 * sizeof(char));
	printf("Numero de primos: ");
	scanf("%s", tmp);
    int int_tmp = atoi(tmp);
    free(tmp);

    if(int_tmp <= 1 ){
        printf("Numero no valido.\n"); 
        return 0;
    }

    if (fork() == 0){
        //Children process
        calcPrimes( int_tmp , getpid());
    }        
    else{
        //Parent process
	    calcPrimes( int_tmp , getpid());
    }
        
	return 0;
}