#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()


int main(int argc, char **argv){

	pid_t processos;
	int fp[2];
	char bf[100], bp[100];
	

	if((pipe(fp)) < 0){
		printf("Erro na criacao do pipe");
	}

	if((processos = fork()) < 0){
		printf("Erro na criacao dos Processos\n");
	}


	//Processo filho
	if(processos == 0){

		//p1
		strcpy(bf, "FILHO: Pai, qual é a verdadeira essência da sabedoria?\n");
		if(write(fp[1], bf, sizeof(bf)) < 0){ 
			printf("erro de comunicação com pipe!\n");
		}
			sleep(1);

		//r2
		if(read(fp[0], bf, sizeof(bf)) < 0){
			printf("erro de comunicação com pipe!\n");

		}else{

			printf("%s", bf);
				
		}
		
			sleep(1);

		//p3
		strcpy(bf, "FILHO: Mas até uma criança de três anos sabe disso!\n");
		if(write(fp[1], bf, sizeof(bf)) < 0){
			printf("erro de comunicação com pipe!\n");
		}
			sleep(1);

		//r4
		if(read(fp[0], bf, sizeof(bf)) < 0){
			printf("erro de comunicação com pipe!\n");

		}else{

			printf("%s", bf);
				
		}
	
		sleep(1);
		exit(0);

	}
	// Processo pai
	else{
		
		//r1
		if(read(fp[0], bp, sizeof(bp)) < 0){
			printf("erro de comunicação com pipe!\n");

		}else{

			printf("%s", bp);
				
		}		

			sleep(1);
		//p2
		strcpy(bp, "PAI: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.\n");
		if(write(fp[1], bp, sizeof(bp)) < 0){
			printf("erro de comunicação com pipe!\n");
		}
			sleep(1);

		//r3
		if(read(fp[0], bp, sizeof(bp)) < 0){
			printf("erro de comunicação com pipe!\n");

		}else{

			printf("%s", bp);
				
		}
			sleep(1);
		//p4
		strcpy(bp, "PAI: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...\n");
		if(write(fp[1], bp, sizeof(bp)) < 0){
			printf("erro de comunicação com pipe!\n");
		}
			sleep(1);
			exit(0);	
	}

return 0; 
}
