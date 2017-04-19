#include <stdio.h>
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()
#include <stdlib.h>	// Para a função exit()
#include <string.h> // Para funções com string
#include <sys/types.h> //para função system()


int main(int argc, char **argv){

	pid_t pid1, pid2;
	int fp[2];
	char bf1[100], bf2[100], bp[100];
	
	if((pipe(fp)) < 0){
		printf("Erro na criacao do pipe");
	}

	if((pid1 = fork()) < 0){
		printf("Erro na criacao do filho1\n");
	}

	
	//Processo filho1
	if(pid1 == 0){

		strcpy(bf1, "FILHO1: Quando o vento passa, é a bandeira que se move.\n");

		if(write(fp[1], bf1, sizeof(bf1)) < 0){
			printf("erro de comunicação com pipe!\n");
		}
			sleep(3);
			exit(0);
	}

	else{
		

		if((pid2 = fork()) < 0){
		printf("Erro na criacao do filho1\n");
		}

		//processo filho 2
		if(pid2 == 0){
			sleep(1);

		strcpy(bf2, "FILHO2: Não, é o vento que se move.\n");

		if(write(fp[1], bf2, sizeof(bf2)) < 0){
			printf("erro de comunicação com pipe!\n");
		}
			sleep(1);

		
		if(read(fp[0], bf2, sizeof(bf2)) < 0){
				printf("erro de comunicação com pipe!\n");
		}else{
				printf("%s\n", bf2);
		}

			sleep(1);
			exit(0);
			

		}

		//processo pai
		else{

			if(read(fp[0], bp, sizeof(bp)) < 0){
				printf("erro de comunicação com pipe!\n");
			}else{
				printf("%s\n", bp);
			}	

				sleep(1);

			if(read(fp[0], bp, sizeof(bp)) < 0){
				printf("erro de comunicação com pipe!\n");
			}else{
				printf("%s\n", bp);
			}	

				sleep(1);


			strcpy(bp, "PAI: Os dois se enganam. É a mente dos senhores que se move.\n");
			if(write(fp[1], bp, sizeof(bp)) < 0){
			printf("erro de comunicação com pipe!\n");
			}
			sleep(1);
			exit(0);

		}
	}

return 0; 
}
