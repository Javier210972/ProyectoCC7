#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <string.h>

struct ingObj {
    int ingId;
    pthread_t tid;
    int direction; //0 derecha, 1 izquierda        
};

pthread_mutex_t bridgeAccess = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bridgeCond = PTHREAD_COND_INITIALIZER;
int peopleOnBridge;
int bridgeDirection; //0 derecha, 1 izquierda 

//Locks para las listas que almacenan los que estan esperando o cruzando
pthread_mutex_t rightMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t leftMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t goingOnMutex = PTHREAD_MUTEX_INITIALIZER;

struct ingObj goToRight[1000];
struct ingObj goToLeft[1000];
struct ingObj goingOnBridge[1000];


void fillArrOfNulls(struct ingObj arr[]){
    int i;
    for(i = 0; i < 1000; i++){
        struct ingObj obj;
        obj.ingId = -1;
        arr[i] = obj;
    }
}

void addIng(struct ingObj arr[], struct ingObj obj){
    int i;
    for(i = 0; i < 1000; i++){
        if(arr[i].ingId == -1){
            arr[i] = obj;
            return;
        }
    }
}

void removeIng(struct ingObj arr[], struct ingObj obj){
    int i;
    for(i = 0; i < 1000; i++){
        if(arr[i].ingId == obj.ingId){
            arr[i].ingId = -1;
            return;
        }
    }
}

void displayIng(struct ingObj arr[]){
    int i;
    for(i = 0; i < 1000; i++){
        if(arr[i].ingId != -1){
            printf("#%d, ", arr[i].ingId);
        }
    }
    printf("\n");
}

void accessBridge(int direction, int ingId){
   pthread_mutex_lock( &bridgeAccess );
    if(peopleOnBridge == 0){        
        bridgeDirection = direction;                       
    }    
     
    while(bridgeDirection != direction || peopleOnBridge == 4){
        pthread_cond_wait( &bridgeCond, &bridgeAccess );
        if(peopleOnBridge == 0){            
            bridgeDirection = direction;               
        }
    }
    if(direction == 0){
        printf("El ing #%d ESTÁ CRUZANDO el puente a la derecha\n", ingId);       
    }else{
        printf("El ing #%d ESTÁ CRUZANDO el puente a la izquierda\n", ingId);       
    } 
    peopleOnBridge++;
    pthread_mutex_unlock( &bridgeAccess );
    pthread_cond_signal( &bridgeCond );
    sleep(rand() % 5);
}

void exitBridge(){
    pthread_mutex_lock( &bridgeAccess );
    peopleOnBridge--;    
    pthread_mutex_unlock( &bridgeAccess );    
    pthread_cond_signal( &bridgeCond );
    
}

void printStatus(){
    pthread_mutex_lock( &rightMutex );
    pthread_mutex_lock( &leftMutex );
    printf("Cola derecha: ");
    displayIng(goToRight);
    printf("Cola izquierda: ");
    displayIng(goToLeft);
    pthread_mutex_unlock( &rightMutex );
    pthread_mutex_unlock( &leftMutex );
}

void *ingComing(void *vargp) {
    sleep(rand() % 15);
    struct ingObj *args = (struct ingObj *)vargp;
    if(args->direction == 0){
        
        printf("LLEGA ing #%d a la cola de la DERECHA\n", args->ingId);
        pthread_mutex_lock( &rightMutex );
        addIng(goToRight, *args);
        pthread_mutex_unlock( &rightMutex );
    }else{
        
        printf("LLEGA ing #%d a la cola de la IZQUIERDA\n", args->ingId);
        pthread_mutex_lock( &leftMutex );
        addIng(goToLeft, *args);
        pthread_mutex_unlock( &leftMutex );
    }

    printStatus();

    accessBridge(args->direction, args->ingId);
    
    if(args->direction == 0){
        pthread_mutex_lock( &rightMutex );
        removeIng(goToRight, *args);
        pthread_mutex_unlock( &rightMutex );
        printf("El ing #%d REGRESO de la derecha y SALIO DEL PUENTE\n", args->ingId);
    }else{
        pthread_mutex_lock( &leftMutex );
        removeIng(goToLeft, *args);
        pthread_mutex_unlock( &leftMutex );
        printf("El ing #%d REGRESO de la izquierda y SALIO DEL PUENTE\n", args->ingId);
    }
    
    exitBridge();


}

int main ( int argc , char * argv []) {
    peopleOnBridge = 0;
    bridgeDirection = -1;
    pthread_mutex_init( &bridgeAccess, NULL );
    char* tmp = (char*)malloc(10 * sizeof(char));
	printf("Ingrese la cantidad de inges que cruzaran: ");
	scanf("%s", tmp);
    int int_tmp = atoi(tmp);
    free(tmp);

    fillArrOfNulls(goToRight);
    fillArrOfNulls(goToLeft);

    struct ingObj ingArr[int_tmp];
    pthread_t tids[int_tmp];

    int i;
    for(i = 0; i < int_tmp; i++){
        struct ingObj actualIng;
        actualIng.ingId = i;
       
        if(rand() % 10 >= 5){
            actualIng.direction = 0;
            printf("El ing #%d camina hacia la derecha.\n", actualIng.ingId);
        }else{
            actualIng.direction = 1;
            printf("El ing #%d camina hacia la izquierda.\n", actualIng.ingId); 
        }

        ingArr[i] = actualIng;        
    }

    for (int i = 0; i < int_tmp; i++){
        pthread_create(&tids[i], NULL, ingComing, (void *)&ingArr[i]);
    }

    for (int i = 0; i < int_tmp; i++){      
        pthread_join(tids[i], NULL);
    }



    /*for(i = 0; i < int_tmp; i++){        
        struct ingObj actualIng = ingArr[i];                                
    }*/
    
    return 0;
}