#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct queuedProcess {
	char *pName;
	int at;
	int bt;
	int v;
	int et;
	int wt;
	int rt;
	int tt;
	int status; 
	int arrived;
	int isRunning;
	int indexInHeaven;
	int runningTicks;

};

//Lo siento, no pude abrir el archivo :S
void fillHeaven(struct queuedProcess heaven[]){
	heaven[0].pName = "P00";
	heaven[0].at = 0;
	heaven[0].bt = 5;
	heaven[0].v = 1;
	heaven[0].status = 0;
	heaven[1].pName = "P01";
	heaven[1].at = 1;
	heaven[1].bt = 5;
	heaven[1].v = 1;
	heaven[1].status = 0;
	heaven[2].pName = "P02";
	heaven[2].at = 2;
	heaven[2].bt = 5;
	heaven[2].v = 1;
	heaven[2].status = 0;
	heaven[3].pName = "P03";
	heaven[3].at = 3;
	heaven[3].bt = 5;
	heaven[3].v = 1;
	heaven[3].status = 0;
	heaven[4].pName = "P04";
	heaven[4].at = 4;
	heaven[4].bt = 5;
	heaven[4].v = 1;
	heaven[4].status = 0;
	heaven[5].pName = "P05";
	heaven[5].at = 0;
	heaven[5].bt = 8;
	heaven[5].v = 2;
	heaven[5].status = 0;
	heaven[6].pName = "P06";
	heaven[6].at = 1;
	heaven[6].bt = 10;
	heaven[6].v = 2;
	heaven[6].status = 0;
	heaven[7].pName = "P07";
	heaven[7].at = 2;
	heaven[7].bt = 7;
	heaven[7].v = 2;
	heaven[7].status = 0;
	heaven[8].pName = "P08";
	heaven[8].at = 0;
	heaven[8].bt = 8;
	heaven[8].v = 3;
	heaven[8].status = 0;
	heaven[9].pName = "P09";
	heaven[9].at = 3;
	heaven[9].bt = 6;
	heaven[9].v = 2;
	heaven[9].status = 0;
	heaven[10].pName = "P10";
	heaven[10].at = 7;
	heaven[10].bt = 3;
	heaven[10].v = 1;
	heaven[10].status = 0;
	heaven[11].pName = "P11";
	heaven[11].at = 9;
	heaven[11].bt = 5;
	heaven[11].v = 2;
	heaven[11].status = 0;
	heaven[12].pName = "P12";
	heaven[12].at = 12;
	heaven[12].bt = 3;
	heaven[12].v = 1;
	heaven[12].status = 0;
	heaven[13].pName = "P13";
	heaven[13].at = 0;
	heaven[13].bt = 7;
	heaven[13].v = 3;
	heaven[13].status = 0;
	heaven[14].pName = "P14";
	heaven[14].at = 2;
	heaven[14].bt = 4;
	heaven[14].v = 3;
	heaven[14].status = 0;
	heaven[15].pName = "P15";
	heaven[15].at = 4;
	heaven[15].bt = 1;
	heaven[15].v = 3;
	heaven[15].status = 0;
	heaven[16].pName = "P16";
	heaven[16].at = 5;
	heaven[16].bt = 4;
	heaven[16].v = 3;
	heaven[16].status = 0;
	heaven[17].pName = "P17";
	heaven[17].at = 0;
	heaven[17].bt = 7;
	heaven[17].v = 1;
	heaven[17].status = 0;
	heaven[18].pName = "P18";
	heaven[18].at = 2;
	heaven[18].bt = 3;
	heaven[18].v = 1;
	heaven[18].status = 0;
	heaven[19].pName = "P19";
	heaven[19].at = 3;
	heaven[19].bt = 5;
	heaven[19].v = 1;
	heaven[19].status = 0;
	heaven[20].pName = "P20";
	heaven[20].at = 6;
	heaven[20].bt = 4;
	heaven[20].v = 1;
	heaven[20].status = 0;
	heaven[21].pName = "P21";
	heaven[21].at = 0;
	heaven[21].bt = 4;
	heaven[21].v = 1;
	heaven[21].status = 0;
	heaven[22].pName = "P22";
	heaven[22].at = 0;
	heaven[22].bt = 3;
	heaven[22].v = 1;
	heaven[22].status = 0;
	heaven[23].pName = "P23";
	heaven[23].at = 0;
	heaven[23].bt = 8;
	heaven[23].v = 2;
	heaven[23].status = 0;
	heaven[24].pName = "P24";
	heaven[24].at = 10;
	heaven[24].bt = 5;
	heaven[24].v = 1;
	heaven[24].status = 0;
	heaven[25].pName = "P25";
	heaven[25].at = 0;
	heaven[25].bt = 10;
	heaven[25].v = 1;
	heaven[25].status = 0;
	heaven[26].pName = "P26";
	heaven[26].at = 0;
	heaven[26].bt = 2;
	heaven[26].v = 1;
	heaven[26].status = 0;
	heaven[27].pName = "P27";
	heaven[27].at = 0;
	heaven[27].bt = 7;
	heaven[27].v = 2;
	heaven[27].status = 0;
	heaven[28].pName = "P28";
	heaven[28].at = 7;
	heaven[28].bt = 6;
	heaven[28].v = 1;
	heaven[28].status = 0;


	int i;
	for(i = 0; i < 29; i++){
		heaven[i].arrived = 0;
		heaven[i].isRunning = 0;
		heaven[i].indexInHeaven = i;
		heaven[i].runningTicks = 0;
		
		heaven[i].et = 0;
		heaven[i].wt = 0;
		heaven[i].rt = 0;
		heaven[i].tt = 0;

	}

}
 

void output(void *vargp) {
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n");
	printf("|PXX\t|UNUSED\t|UNUSED\t|AT\t|BT\t|ET\t|WT\t|RT\t|TT\t|TT\t|\n");
	printf("|-------|-------|-------|-------|-------|-------|-------|-------|-------| \n\n");
}

struct queuedProcess nextOnTick(int tick, struct queuedProcess heaven[]){

	struct queuedProcess toReturn;
	toReturn.pName = "NOTFOUND";
	toReturn.status = -1;

	int i;
	for(i = 0; i < 29; i++){
		struct queuedProcess actualQP = heaven[i];
		if(actualQP.at == tick  && actualQP.status == 0){
			toReturn = actualQP;
			toReturn.status = 1;
			
			heaven[i] = toReturn;
			return toReturn;
		}
	}

	
	return toReturn;
}

void arriveFCFS(struct queuedProcess qp, int tick, struct queuedProcess heaven[]){
	qp.arrived = 1;
	heaven[qp.indexInHeaven] = qp;
}

void processFCFSTick(int tick, struct queuedProcess heaven[]){
	int i;
	int somebodyRunning = 0;
	for(i = 0; i <29; i++){
		//Si un proceso ya termino
		if(heaven[i].runningTicks == heaven[i].bt && heaven[i].isRunning == 1){
			heaven[i].et = tick;
			heaven[i].isRunning = 0;
		}

		//Alguien que llego pero no esta corriendo
		if(heaven[i].arrived == 1 && heaven[i].isRunning == 0 && heaven[i].et == 0 ){
			heaven[i].wt++;
		}
		//Alguien que llego y esta corriendo
		if(heaven[i].arrived == 1 && heaven[i].isRunning == 1){
			heaven[i].runningTicks++;
		}
		
	}

	for(i = 0; i <29; i++){
		if(heaven[i].isRunning == 1){
			somebodyRunning = 1;		
		}
	}
	
	//Si nadie esta corriendo, voy yo
	int k;
	int l;
	
	if(!somebodyRunning){			
		for(k = 0; k < 200; k++){
			for(l = 0; l < 29; l++){
				if(heaven[l].at == k && heaven[l].arrived == 1 && heaven[l].et == 0){
					heaven[l].isRunning = 1;
					heaven[i].rt = tick - heaven[i].at;
					return;
				}
			}
		}			
	}
}

void FCFS(void *vargp) {
		
	struct queuedProcess heaven[29];
	fillHeaven(heaven);
	

	int ticks = 0;
	int idSTATUS;
	while(ticks < 200){
		//One tick activitie

		while(1){
			struct queuedProcess qp = nextOnTick(ticks, heaven);
			if(qp.status == -1){								
				break;
			}else{
				arriveFCFS(qp, ticks, heaven);				
			}
		}	
		processFCFSTick(ticks, heaven);
		ticks++;
	}

	output(0);
	int i;
	for(i = 0; i < 29; i++){
		printf("|%s\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|%d\t|\n",
		heaven[i].pName,
		0,
		0,
		heaven[i].at,
		heaven[i].bt,
		heaven[i].et  - 1,
		heaven[i].wt - 1,
		heaven[i].wt,
		heaven[i].et - heaven[i].at,
		heaven[i].bt + heaven[i].wt
		);
	}
	
} 

void PS(void *vargp) {
	FCFS(0);
	printf("Mostrando FCFS (no implemente PS)\n");
} 

void RR(void *vargp) {
	FCFS(0);
	printf("Mostrando FCFS (no implemente RR)\n");
} 

void MLFQS(void *vargp) {
	FCFS(0);
	printf("Mostrando FCFS (no implemente MLFQS)\n");
} 

int menu(){
	int tmp;
	
	printf("############\n1 - FCFS\n2 - PS\n3 - RR\n4 - MLFQS\n0 - EXIT\n\nSeleccione Opción: ");
	scanf("%d", &tmp);
	return tmp;
}

// C Concepts 
// https://gist.github.com/Integralist/6c35d4f26c0c7bf5bdce7b95cfa906b3
int main ( int argc , char * argv []) {
	
	int op = 9;
	pid_t pid;
	printf("(Los datos están quemados en el programa, no se leen del archivo)\n");
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
			FCFS(0);
			break;
			case 2:
			PS(0);
			break;
			case 3:
			RR(0);
			break;
			default:
			case 4:
			MLFQS(0);
			break;
		}
	}
	return 0;
}