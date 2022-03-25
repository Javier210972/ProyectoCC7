#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <string.h>

struct alqElement {
    int alqId;
    pthread_t tid;
    int type; //0 -> O, 1 -> H, 2 -> N
};

int cantOxigeno;
int cantHidrogeno;
int cantNitrogeno;

int cantidadFuego;
int cantFuegosProducidos;

int killElementsFlag;

struct alqElement elementsArr[1200];

pthread_mutex_t cantMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cantCond = PTHREAD_COND_INITIALIZER;

void fillArrOfNulls(struct alqElement arr[]){
    int i;
    for(i = 0; i < 1200; i++){
        struct alqElement obj;
        obj.alqId = -1;
        arr[i] = obj;
    }
}

void addAlq(struct alqElement arr[], struct alqElement obj){
    int i;
    for(i = 0; i < 1200; i++){
        if(arr[i].alqId == -1){
            arr[i] = obj;
            return;
        }
    }
}

void searchAndRemoveElement(struct alqElement arr[], int type, int quantity){
    int deletedItems = 0;
    int i;
    for(i = 0; i < 1200; i++){
        if(deletedItems >= quantity){
            return;
        }
        
        if(arr[i].type == type && arr[i].alqId != -1 && arr[i].alqId != -2){
            if(arr[i].type == 0){
                printf("SE USÓ el elemento id%d de tipo Oxigeno \n", arr[i].alqId);       
            }
            
            if(arr[i].type == 1){
                printf("SE USÓ el elemento id%d de tipo Hidrogeno \n", arr[i].alqId);       
            }
            
            if(arr[i].type == 2){
                printf("SE USÓ el elemento id%d de tipo Nitrogeno \n", arr[i].alqId);       
            }
            
            arr[i].alqId = -2;
            deletedItems++;            
        }
    }
}
//Unificacion de los metodos Ni() Hi() Ox()
void *elementComing(void *vargp) {
    sleep(rand() % 15);
    struct alqElement *args = (struct alqElement *)vargp;
    if(args->type == 0){
        //Oxigeno
        pthread_mutex_lock( &cantMutex );
        cantOxigeno++;
        printf("Se crea id%d Oxigeno \n", args->alqId);
        addAlq(elementsArr, *args);
        pthread_mutex_unlock( &cantMutex );
        pthread_cond_signal( &cantCond);
    }
    if(args->type == 1){
        //Hidrogeno
        pthread_mutex_lock( &cantMutex );
        cantHidrogeno++;
        printf("Se crea id%d Hidrogeno \n", args->alqId);
        addAlq(elementsArr, *args);
        pthread_mutex_unlock( &cantMutex );                
        pthread_cond_signal( &cantCond);
    }
    if(args->type == 2){
        //Nitrogeno
        pthread_mutex_lock( &cantMutex );
        cantNitrogeno++;
        printf("Se crea id%d Nitrogeno \n", args->alqId);
        addAlq(elementsArr, *args);
        pthread_mutex_unlock( &cantMutex );                
        pthread_cond_signal( &cantCond);
    }

    pthread_mutex_lock( &cantMutex );

    while(cantNitrogeno < 1 || cantHidrogeno < 3 || cantOxigeno < 2){        
        pthread_cond_wait( &cantCond, &cantMutex );
        if(killElementsFlag == 1){            
            pthread_mutex_unlock( &cantMutex );
            return 0;
        }
    }
    
    cantHidrogeno -= 3;
    cantNitrogeno -= 1;
    cantOxigeno -= 2;    
    printf("FUEGOOOO!!!! \n");  
    searchAndRemoveElement(elementsArr, 0, 2);
    searchAndRemoveElement(elementsArr, 1, 3);
    searchAndRemoveElement(elementsArr, 2, 1);

    cantFuegosProducidos++; 
    if(cantFuegosProducidos == cantidadFuego){
        killElementsFlag = 1;
    } 
    
    pthread_mutex_unlock( &cantMutex );
    pthread_cond_broadcast( &cantCond);    
}

int main ( int argc , char * argv []) {
    cantOxigeno = 0;
    cantHidrogeno = 0;
    cantNitrogeno = 0;
    cantFuegosProducidos = 0;
    killElementsFlag = 0;

    fillArrOfNulls(elementsArr);

    char* tmp = (char*)malloc(10 * sizeof(char));
	printf("Cantidad reacciones a crear: ");
	scanf("%s", tmp);
    int int_tmp = atoi(tmp);
    free(tmp);    

    cantidadFuego = int_tmp;
    struct alqElement alqArr[(int_tmp * 1) + (int_tmp * 2) + (int_tmp * 3)];
    pthread_t tids[(int_tmp * 1) + (int_tmp * 2) + (int_tmp * 3)];

    //Atomos de Oxigeno
    int i;
    for(i = 0; i < (int_tmp * 2); i++){
        struct alqElement actualElement;
        actualElement.alqId = i;
        actualElement.type = 0;
        alqArr[i] = actualElement;
    }

    //Atomos Hidrogeno
    for(i = i; i < ((int_tmp * 2) + (int_tmp * 3)); i++){
        struct alqElement actualElement;
        actualElement.alqId = i;
        actualElement.type = 1;
        alqArr[i] = actualElement;
    }

    //Atomos Nitrogeno
    for(i = i; i < ((int_tmp * 1) + (int_tmp * 2) + (int_tmp * 3)); i++){
        struct alqElement actualElement;
        actualElement.alqId = i;
        actualElement.type = 2;
        alqArr[i] = actualElement;
    }

    for (i = 0; i < (int_tmp * 1) + (int_tmp * 2) + (int_tmp * 3); i++){
        pthread_create(&tids[i], NULL, elementComing, (void *)&alqArr[i]);
    }

    for (i = 0; i < (int_tmp * 1) + (int_tmp * 2) + (int_tmp * 3); i++){
        pthread_join(tids[i], NULL);
    }
    
    return 0;
}