#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void FIFO(void *vargp) {
	int fifoArr[1000];
	
	//Planchando la memoria
	int i;
	for(i = 0; i < 1000; i++){
		fifoArr[i] = -1;
	}
	fillArray(fifoArr);

	int inputListSize = realListSize(fifoArr);
	int initialPosition = getInitialPosition();
	printf("\n");

	if(initialPosition < 0 || initialPosition > 100){
		printf("POSICION INICIAL DE CABEZA NO VALIDA \n");
		return;
	}
	
	printf("\n");
	printf("FCFS - FIFO \n");
	printf("Posicion Inicial: %d \n", initialPosition);
	printf("Listado: ");
	int j;
	for(j = 0; j < inputListSize; j++){
		printf("%d,",fifoArr[j]);
	}
	printf("\n");
	int cabeza;
	cabeza = initialPosition;
	int recorridos[inputListSize];
	int recorridosTot; 
	recorridosTot = 0;
	int k;
	for(k = 0; k < inputListSize; k++){
		recorridos[k] = abs(cabeza - fifoArr[k]);
		recorridosTot += abs(cabeza - fifoArr[k]);
		cabeza = fifoArr[k];
	}

	float promedio = recorridosTot / inputListSize;
	
	printf("Promedio: %.2f \n",promedio );
	
	int deSumatoria;
	int l;
	for ( l = 0; l < inputListSize; l++ ){
		deSumatoria += abs(recorridos[l] - promedio ) * abs(recorridos[l] - promedio );
	}

	

	float desviacionEstandar = pow( deSumatoria / inputListSize, 0.5);

	printf("Desviacion estandar: %.2f \n",desviacionEstandar );

	printf("\n");
	printf("\n");

} 

void SCAN(void *vargp) {
	int fifoArr[1000];
	
	//Planchando la memoria
	int i;
	for(i = 0; i < 1000; i++){
		fifoArr[i] = -1;
	}
	fillArray(fifoArr);

	int inputListSize = realListSize(fifoArr);
	int initialPosition = getInitialPosition();
	printf("\n");

	if(initialPosition < 0 || initialPosition > 100){
		printf("POSICION INICIAL DE CABEZA NO VALIDA \n");
		return;
	}
	
	printf("\n");
	printf("SCAN \n");
	printf("Posicion Inicial: %d \n", initialPosition);
	printf("Listado: ");
	int j;
	for(j = 0; j < inputListSize; j++){
		//printf("%d,",fifoArr[j]);
	}
	
	int cabeza;
	cabeza = initialPosition;

	int recorridos[100];
	int k;
	for(k = 0; k < 100; k++){
		recorridos[i] = -1;
	}

	int recorridosTot; 
	recorridosTot = 0;
	int direction = 1;

	int ultimoLeido = cabeza;
	//Brazo de posicion inicial a la derecha
	for(cabeza = cabeza; cabeza < 101; cabeza++){

		if(isInArray(fifoArr, inputListSize, cabeza)){
			recorridos[cabeza] = abs(cabeza - ultimoLeido);
			recorridosTot += abs(cabeza - ultimoLeido);
			printf("%d,",cabeza);
			ultimoLeido = cabeza;
		}

	}
	//Brazo de posicision inicial a la izquierda
	int primeraVez = 1;
	for(cabeza = initialPosition; cabeza >= 0; cabeza--){

		if(isInArray(fifoArr, inputListSize, cabeza)){
			
			recorridos[cabeza] = abs(cabeza - ultimoLeido) + initialPosition;
			recorridosTot += abs(cabeza - ultimoLeido) + initialPosition;
			printf("%d,",cabeza);
			if(primeraVez){
				//Se le suma initialPosition para simular lo recorrido de 100 al punto de inicio la primera vez
				recorridos[cabeza] += initialPosition;
				recorridosTot += initialPosition;

				primeraVez = 0;
			}
			ultimoLeido = cabeza;
		}

	}

	float promedio = recorridosTot / inputListSize;
	printf("\n");
	printf("Promedio: %.2f \n",promedio );
	
	int deSumatoria;
	int l;
	for ( l = 0; l < 100; l++ ){
		if(recorridos[l] != -1){
			deSumatoria += abs(recorridos[l] - promedio ) * abs(recorridos[l] - promedio );
		}
		
	}


	float desviacionEstandar = pow( deSumatoria / inputListSize, 0.5);

	printf("Desviacion estandar: %.2f \n",desviacionEstandar );

	printf("\n");
	printf("\n");


} 

void CSCAN(void *vargp) {
	int fifoArr[1000];
	
	//Planchando la memoria
	int i;
	for(i = 0; i < 1000; i++){
		fifoArr[i] = -1;
	}
	fillArray(fifoArr);

	int inputListSize = realListSize(fifoArr);
	int initialPosition = getInitialPosition();
	printf("\n");

	if(initialPosition < 0 || initialPosition > 100){
		printf("POSICION INICIAL DE CABEZA NO VALIDA \n");
		return;
	}
	
	printf("\n");
	printf("CSCAN \n");
	printf("Posicion Inicial: %d \n", initialPosition);
	printf("Listado: ");
	int j;
	for(j = 0; j < inputListSize; j++){
		//printf("%d,",fifoArr[j]);
	}
	
	int cabeza;
	cabeza = initialPosition;

	int recorridos[100];
	int k;
	for(k = 0; k < 100; k++){
		recorridos[i] = -1;
	}

	int recorridosTot; 
	recorridosTot = 0;
	int direction = 1;

	int ultimoLeido = cabeza;
	//Brazo de posicion inicial a la derecha desde posicion inicial
	for(cabeza = cabeza; cabeza < 101; cabeza++){

		if(isInArray(fifoArr, inputListSize, cabeza)){
			recorridos[cabeza] = abs(cabeza - ultimoLeido);
			recorridosTot += abs(cabeza - ultimoLeido);
			printf("%d,",cabeza);
			ultimoLeido = cabeza;
		}

	}
	//Brazo desde 0 a posicion inicial
	int primeraVez = 1;
	for(cabeza = 0; cabeza < initialPosition; cabeza++){

		if(isInArray(fifoArr, inputListSize, cabeza)){
			
			recorridos[cabeza] = abs(cabeza - ultimoLeido);
			recorridosTot += abs(cabeza - ultimoLeido);
			if(primeraVez){
				//Se le suma 100 para simular lo recorrido del fin al inicio del disco
				recorridos[cabeza] += 100;
				recorridosTot += 100;
				primeraVez = 0;
			}
			printf("%d,",cabeza);
			ultimoLeido = cabeza;
		}

	}

	float promedio = recorridosTot / inputListSize;
	printf("\n");
	printf("Promedio: %.2f \n",promedio );
	
	int deSumatoria;
	int l;
	for ( l = 0; l < 100; l++ ){
		if(recorridos[l] != -1){
			deSumatoria += abs(recorridos[l] - promedio ) * abs(recorridos[l] - promedio );
		}
		
	}


	float desviacionEstandar = pow( deSumatoria / inputListSize, 0.5);

	printf("Desviacion estandar: %.2f \n",desviacionEstandar );

	printf("\n");
	printf("\n");

} 

void SSTF(void *vargp) {
	int fifoArr[1000];
	
	//Planchando la memoria
	int i;
	for(i = 0; i < 1000; i++){
		fifoArr[i] = -1;
	}
	fillArray(fifoArr);

	int inputListSize = realListSize(fifoArr);
	int initialPosition = getInitialPosition();
	printf("\n");

	if(initialPosition < 0 || initialPosition > 100){
		printf("POSICION INICIAL DE CABEZA NO VALIDA \n");
		return;
	}
	
	printf("\n");
	printf("SSTF \n");
	printf("Posicion Inicial: %d \n", initialPosition);
	printf("Listado: ");
	int j;
	for(j = 0; j < inputListSize; j++){
		//printf("%d,",fifoArr[j]);
	}
	
	int cabeza;
	cabeza = initialPosition;
	int recorridos[inputListSize];
	int recorridosTot; 
	recorridosTot = 0;
	int k;

	for(k = 0; k < inputListSize; k++){
		int distances[inputListSize];
		int a;
		for(a = 0; a < inputListSize; a++){
			
			if(fifoArr[a] == -1){
				distances[a] = 999;
			}else{
				distances[a]  = abs(cabeza - fifoArr[a]);
			}
			
		}

		int minIndex = findMinIndex(distances, inputListSize);
		
		recorridos[k] = abs(cabeza - fifoArr[minIndex]);
		recorridosTot += abs(cabeza - fifoArr[minIndex]);
		cabeza = fifoArr[minIndex];
		printf("%d,",cabeza);
		fifoArr[minIndex]  = -1;
		
	}

	float promedio = recorridosTot / inputListSize;
	printf("\n");
	printf("Promedio: %.2f \n",promedio );
	
	int deSumatoria;
	int l;
	for ( l = 0; l < inputListSize; l++ ){
		deSumatoria += abs(recorridos[l] - promedio ) * abs(recorridos[l] - promedio );
	}

	

	float desviacionEstandar = pow( deSumatoria / inputListSize, 0.5);

	printf("Desviacion estandar: %.2f \n",desviacionEstandar );

	printf("\n");
	printf("\n");

} 

int menu(){
	int tmp;
	printf("############\n1 - FIFO\n2 - SCAN\n3 - CSCAN\n4 - SSTF\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}

int fillArray(int numArr[]){
	int i;
	int answer;
	i = 0;
	while(1){
		printf("(Ingrese -1 para dejar de agregar)\n");
		printf("Ingrese un requerimiento (numero entero): ");
		scanf("%d", &answer);
		if(answer < 0){
			return;
		}
		if(answer > 100){
			printf("Numero mayor a 100 invalido. Se tomaran en cuenta solo los numeros anteriores.\n");
			return;
		}
		numArr[i] = answer;
		i++;
	}
}

void displayArray(int numArr[]){
	int i;
	for(i = 0; i < 1000; i++){
		if(numArr[i] == -1){
			return;
		}
		printf("%d \n", numArr[i]);
	}
}

int realListSize(int numArr[]){
	int i;
	int size;
	size = 0;
	for(i = 0; i < 1000; i++){
		if(numArr[i] == -1){
			return size;
		}else{
			size++;
		}
	}
	
}

int getInitialPosition(){
	printf("INGRESE POSICION INICIAL DE LA CABEZA LECTORA: ");
	int tmp;
	scanf("%d", &tmp);
	return tmp;
}

int abs(int x){
	if(x >= 0){
		return x;
	}else{
		return -1 * x;
	}
}

int isInArray(int arr[], int arrL, int x){
	int isIn = 0;
	int i;
	for(i =0; i <arrL;i++){
		if(arr[i] == x){
			isIn = 1;
			break;
		}
	}
	return isIn;
}

int specialIsEmpty(int arr[], int arrL ){
	int i;
	for(i =0; i <arrL;i++){
		if(arr[i] != -1){
			return 0;
		}
	}
	return 1;
}

int findMinIndex(int arr[], int arrL ){
	int min;
	int i;
	for(i =0; i <arrL;i++){
		if(arr[i] != 0){
			min = arr[i];
			break;
		}
	}

	for(i =0; i <arrL;i++){
		if(arr[i] != 0){
			if(arr[i] < min){
				min = arr[i]; 
			}
		}
	}

	for(i =0; i <arrL;i++){
		if(arr[i] == min){
			return i;
		}
	}

	return -1;
}
// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main ( int argc , char * argv []) {
	printf("LAB 4 RICARDO ZELADA \n");
	int op = 9;
	pid_t pid;
	while (op > 0){
		op = menu();
		printf("Procesando opción: %d\n", op);
		if ( op >5 || op<=0 ){
			printf("### END ###\n");
			break;
		}
		printf("### BEGIN ###\n");
		switch(op){
			case 1:
			FIFO(0);
			break;
			case 2:
			SCAN(0);
			break;
			case 3:
			CSCAN(0);
			break;
			default:
			case 4:
			SSTF(0);
			break;
		}
	}
	return 0;
}